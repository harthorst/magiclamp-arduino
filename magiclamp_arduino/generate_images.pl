#/usr/bin/perl

use Graphics::Magick;
use List::Util qw[min max];

$width  = 40;
$height = 40;

$image=Graphics::Magick->new;
$image->Read("images/*.png");

$filename = "imagesX.h";
open(my $fh, '>', $filename) or die "Could not open file '$filename' $!";

print $fh "static const uint8_t IMAGE_WIDTH = $width;\n";
print $fh "static const uint8_t IMAGE_HEIGHT = $height;\n";

print $fh "static const uint8_t image_data_images[".@$image."][$width*$height] PROGMEM = {\n";

for ($i = 0; $image->[$i]; $i++) {
	if ($i>0) {
		print $fh ",";
	}
	print $fh "{\n";

	$image->[$i]->Set(depth => 8);
	#$image->[$i]->Quantize(colorspace => 'Gray');
	$image->[$i]->Resize(width => $width, height => $height, blur => 0);
    $image->[$i]->Write("$i.png");
    
    for ($y = 0; $y < $height; $y++) {
    	for ($x = 0; $x < $width; $x++) {
    		if ($x>0 || $y>0) {
    			print $fh ',';
    		}
    		$pixelString = $image->[$i]->Get("pixel[$x,$y]");
    		#print $pixelString;
    		my ($r,$g,$b) = (split /,/, $pixelString);
    		$r = min(255, $r / 16 ** 2);
    		
    		printf $fh "%3.0f", "$r";
    	}
    print $fh "\n";
    }
    print $fh "}\n";
}

print $fh '};';