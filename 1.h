/*****************************************************
 *	C++ code generated with Nana Creator (0.32.0)
 *	GitHub repo: https://github.com/besh81/nana-creator
 *
 * PLEASE EDIT ONLY INSIDE THE TAGS:
 *		//<*tag
 *			user code
 *		//*>
*****************************************************/

#ifndef nana_comp_test_H_
#define nana_comp_test_H_

#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/panel.hpp>
#include <nana/gui/widgets/spinbox.hpp>
#include <nana/gui/widgets/checkbox.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/progress.hpp>
#include <nana/gui/widgets/button.hpp>

//<*includes

//*>


class nana_comp_test
	: public nana::form
{
public:
	nana_comp_test(nana::window wd, const ::nana::size& sz = {640, 480}, const nana::appearance& apr = {true, true, false, false, false, false, false})
		: nana::form(wd, sz, apr)
	{
		init_();
		//<*ctor
		show();
		
		//*>
	}

	~nana_comp_test()
	{
		//<*dtor

		//*>
	}


private:
	void init_()
	{
		place_.bind(*this);
		place_.div("margin=[5,5,5,5] <grid=[1,3] margin=[5,5,5,5] gap=2 Null_5>");
		caption("Form");
		// Null_6
		Null_6.create(*this);
		Null_6_place_.bind(Null_6);
		Null_6_place_.div("margin=[5,5,5,5] <margin=[5,5,5,5] gap=2 Null_4>");
		place_["Null_5"] << Null_6;
		// Null_7
		Null_7.create(Null_6);
		Null_7_place_.bind(Null_7);
		Null_7_place_.div("margin=[5,5,5,5] <vert margin=[5,5,5,5] gap=2 Null_8>");
		Null_6_place_["Null_4"] << Null_7;
		// Null_0
		Null_0.create(Null_7);
		Null_7_place_["Null_8"] << Null_0;
		// N_point_set
		N_point_set.create(Null_7);
		Null_7_place_["Null_8"] << N_point_set;
		// Null_1
		Null_1.create(Null_7);
		Null_7_place_["Null_8"] << Null_1;
		// Null_9
		Null_9.create(Null_6);
		Null_9_place_.bind(Null_9);
		Null_9_place_.div("margin=[5,5,5,5] <vert margin=[5,5,5,5] gap=2 Null_10>");
		Null_6_place_["Null_4"] << Null_9;
		// Point_in_file
		Point_in_file.create(Null_9);
		Null_9_place_["Null_10"] << Point_in_file;
		Point_in_file.caption("");
		Point_in_file.radio(true);
		// Auto_gen
		Auto_gen.create(Null_9);
		Null_9_place_["Null_10"] << Auto_gen;
		Auto_gen.caption("");
		Auto_gen.radio(true);
		// checkbox11
		checkbox11.create(Null_9);
		Null_9_place_["Null_10"] << checkbox11;
		checkbox11.caption("");
		checkbox11.radio(true);
		// Null_11
		Null_11.create(*this);
		Null_11_place_.bind(Null_11);
		Null_11_place_.div("margin=[5,5,5,5] <vert margin=[5,5,5,5] gap=2 Null_12>");
		place_["Null_5"] << Null_11;
		// Null_2
		Null_2.create(Null_11);
		Null_11_place_["Null_12"] << Null_2;
		// textbox1
		textbox1.create(Null_11);
		Null_11_place_["Null_12"] << textbox1;
		// textbox2
		textbox2.create(Null_11);
		Null_11_place_["Null_12"] << textbox2;
		// Null_13
		Null_13.create(*this);
		Null_13_place_.bind(Null_13);
		Null_13_place_.div("margin=[5,5,5,5] <vert margin=[5,5,5,5] gap=2 Null_14>");
		place_["Null_5"] << Null_13;
		// Null_3
		Null_3.create(Null_13);
		Null_13_place_["Null_14"] << Null_3;
		// progress
		progress.create(Null_13);
		Null_13_place_["Null_14"] << progress;
		// Null_15
		Null_15.create(Null_13);
		Null_15_place_.bind(Null_15);
		Null_15_place_.div("margin=[5,5,5,5] gap=2 _field_");
		Null_13_place_["Null_14"] << Null_15;
		// Start_BTN
		Start_BTN.create(Null_15);
		Null_15_place_["_field_"] << Start_BTN;
		Start_BTN.caption("button");

		place_.collocate();
		Null_6_place_.collocate();
		Null_7_place_.collocate();
		Null_9_place_.collocate();
		Null_11_place_.collocate();
		Null_13_place_.collocate();
		Null_15_place_.collocate();
	}


protected:
	nana::place place_;
	nana::panel<true> Null_6;
	nana::place Null_6_place_;
	nana::panel<true> Null_7;
	nana::place Null_7_place_;
	nana::panel<true> Null_0;
	nana::panel<true> Null_1;
	nana::panel<true> Null_9;
	nana::place Null_9_place_;
	nana::panel<true> Null_11;
	nana::place Null_11_place_;
	nana::panel<true> Null_2;
	nana::panel<true> Null_13;
	nana::place Null_13_place_;
	nana::panel<true> Null_3;
	nana::panel<true> Null_15;
	nana::place Null_15_place_;

	nana::spinbox N_point_set;
	nana::checkbox Point_in_file;
	nana::checkbox Auto_gen;
	nana::checkbox checkbox11;
	nana::textbox textbox1;
	nana::textbox textbox2;
	nana::progress progress;
	nana::button Start_BTN;


	//<*declarations

	//*>
};

#endif //nana_comp_test_H_

