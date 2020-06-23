#include "Sound.h"

irrklang::ISoundSource* sound;

void Sound::setSoundSource(irrklang::ISoundSource* soundSource) {
	sound = soundSource;
}