#pragma once

#include "..\..\includes.hpp"
#include "..\..\sdk\structs.hpp"

class engineprediction : public singleton< engineprediction > {
public:
	void start( );
	void finish() const;
private:
	int m_tickbase_backup;
	int m_flags_backup;
	float orig_currtime = 0.f;
	float orig_frametime = 0.f;
	int * m_random_seed;
	int * m_prediction_player;
	char * m_movedata = nullptr;
};