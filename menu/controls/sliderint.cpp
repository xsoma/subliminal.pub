#include "..\cmenu.hpp"

#define gg 9

C_SliderInt::C_SliderInt( std::string n_label, int * n_value, int n_min, int n_max, std::string n_follower, std::vector< C_ControlFlag * > n_flags ) {
	parent = g_cfg.menu.last_group;
	label = n_label;
	value = n_value;
	min = n_min;
	max = n_max;
	follower = n_follower;

	flags = n_flags;

	area.h = 15;

	if ( n_label != "" ) {
		height_offset = 14;
		area.h += 14;
	}

	parent->add_control( this );
}

void C_SliderInt::draw( ) {
	rect_t n_area = area;

	render::get( ).text( fonts[ TAHOMA12 ], area.x, area.y, Color::White, HFONT_CENTERED_NONE, label.c_str( ) );
	n_area.y += height_offset;
	n_area.h -= height_offset;
	n_area.x += 12;
	n_area.w -= 24;

	POINT mouse; GetCursorPos( &mouse );
	rect_t item_region = rect_t( n_area.x, n_area.y, n_area.w, gg );

	if ( item_region.contains_point( mouse ) ) {
		render::get( ).rect_filled( n_area.x, n_area.y, n_area.w, gg, Color { 30, 30, 30, 255 } );
	}
	else
		render::get( ).rect_filled( n_area.x, n_area.y, n_area.w, gg, Color { 24, 24, 24, 255 } );

	float ratio = ( *value - min ) / ( max - min );
	float location = ratio * n_area.w;

	render::get( ).rect_filled( n_area.x, n_area.y, location, gg, g_cfg.menu.menu_theme[ 0 ] );

	render::get( ).rect( n_area.x, n_area.y, n_area.w, gg, Color{ 49, 49, 49 });

	std::stringstream ss;
	ss << *value << follower.c_str( );

	render::get( ).text( fonts[ TAHOMA12 ], n_area.x + location, n_area.y + 6, Color::White, HFONT_CENTERED_X, ss.str( ).c_str( ) );


	render::get().text(fonts[TAHOMA12], n_area.x - 9, n_area.y - 2, Color::White, HFONT_CENTERED_X, "-");
	render::get().text(fonts[TAHOMA12], n_area.x + n_area.w + 8, n_area.y - 2, Color::White, HFONT_CENTERED_X, "+");
}

void C_SliderInt::update( ) {
	if ( dragging ) {
		if ( GetAsyncKeyState( VK_LBUTTON ) ) {
			POINT mouse;  GetCursorPos( &mouse );

			float
				new_x,
				ratio;

			area.x += 12;
			area.w -= 24;

			new_x = mouse.x - area.x;

			if ( new_x < 0 ) { new_x = 0; }
			if ( new_x > area.w ) { new_x = area.w; }

			ratio = new_x / float( area.w );
			*value = min + ( max - min ) * ratio;

			area.x -= 12;
			area.w += 24;
		}
		else {
			dragging = false;
		}
	}
}

void C_SliderInt::click( ) {
	dragging = true;
}