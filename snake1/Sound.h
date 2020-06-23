#ifndef SOUND_H
#define SOUND_H
#include <irrKlang/irrKlang.h>

class Sound {
public:
	irrklang::ISoundSource* sound;
	void setSoundSource(irrklang::ISoundSource* soundSource);
};


#endif
