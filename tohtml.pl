#!/usr/bin/perl

my @overlay;

if( $#ARGV == 1) {
	@overlay = readFile($ARGV[1]);
}else{
	@overlay = (
		"111222333",
		"111222333",
		"111222333",
		"444555666",
		"444555666",
		"444555666",
		"777888999",
		"777888999",
		"777888999"
	);
}
my @sud = readFile($ARGV[0]);
&genHTML(@overlay,@sud);

sub readFile {
	open FILE, "<", $_[0] or die $!;
	binmode FILE;
	@lines = <FILE>;
	$_ = join("", @lines);
	close FILE;
	if( /([0-9]{9,9}\r?\n){8,8}([0-9]{9,9}\r?\n?)/ ) {
		foreach(@lines) {
			s/\r?\n//g
		}
		return @lines;
	}
	die "Konnte Datein nicht einlesen!\n";
}

sub genHTML {
	printHead();
	for($i=0;$i<9;$i++) {
		print "\t\t\t<tr>\n";
		for($j=0;$j<9;$j++) {
			print "\t\t\t\t<td class=\"c" , substr($overlay[$i],$j,1) , "\">" , substr($sud[$i],$j,1) , "</td>\n";
		}
		print "\t\t\t</tr>\n";
	}
	printFoot();
}

sub printHead {
	print <<EOT
<!DOCTYPE html>
<html>
	<head>
		<title>Sudoku (solved)</title>
		<style type="text/css">
			.c1{background:#c8ffc8}.c2{background:#ffff66}.c3{background:#83caff}.c4{background:#ff950e}.c5{background:#0084d1}.c6{background:#aecf00}.c7{background:#ffc8c8}.c8{background:#00ffff}.c9{background:#c8c8ff}
			table{border-collapse:collapse}td{border:1px solid #000;height:3em;width:3em;text-align:center;vertical-align:middle;font-weight:bold}
		</style>
	</head>
	<body>
		<table>
EOT
}

sub printFoot {
	print <<EOT
		</table>
	</body>
</html>
EOT
}
