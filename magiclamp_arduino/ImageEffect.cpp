#include "Graph.h"
#include "ImageEffect.h"
#include "Const.h"
#include "Arduino.h"
#include <FastLED.h>
#include "imagesX.h"

ImageEffect::ImageEffect(CRGB *leds) {
	_leds = leds;
}

void ImageEffect::update() {
	int image = 2;
	int offsetX  = sin8(millis() / 50) / 2;
	int offsetY  = sin8(millis() / 50) / 2;

	int realOffsetX = offsetX / 10;
	int remainderX = offsetX % 10;
	int realOffsetY = offsetY / 10;
	int remainderY = offsetY % 10;

	for (int i = 0; i < NUM_LEDS; i++) {
		uint32_t index1 = (((realOffsetX + graph.getX(i))     % IMAGE_WIDTH) * scale) + ((((realOffsetY + graph.getY(i)))    % IMAGE_HEIGHT) * scale) * IMAGE_WIDTH;
		uint8_t color1 = pgm_read_word(&image_data_images[image][index1]);
		uint32_t index2 = (((realOffsetX + graph.getX(i))     % IMAGE_WIDTH) * scale) + ((((1+ realOffsetY + graph.getY(i))) % IMAGE_HEIGHT) * scale) * IMAGE_WIDTH;
		uint8_t color2 = pgm_read_word(&image_data_images[image][index2]);
		uint32_t index4 = (((1 + realOffsetX + graph.getX(i)) % IMAGE_WIDTH) * scale) + ((((realOffsetY + graph.getY(i)))    % IMAGE_HEIGHT) * scale) * IMAGE_WIDTH;
		uint8_t color4 = pgm_read_word(&image_data_images[image][index4]);

		uint32_t color = (((10 - remainderX) * color1)
				+ remainderX * color4
				+ remainderY * color2
				+ (10 - remainderY) * color1) / 40;

		//index1 = (((realOffsetX + graph.getX(i)))) + ((((realOffsetY + graph.getY(i))))) * (IMAGE_WIDTH);
		//color = pgm_read_word(&image_data_images[image][index1]);


/*
		Serial.print(i);
		Serial.print(" - ");
		Serial.println(color);*/
		_leds[i] = CHSV(128, 255, color);
	}


	FastLED.show();
}

void ImageEffect::init() {


	Serial.println("---");
	for (int i = 0; i< COLUMNS; i++) {
		for (int k = 0; k<COUNT_A * 2; k++) {
			//Serial.print(image[i][k]);
		}
		//Serial.println("---");
	}
}


