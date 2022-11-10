#include "DSCEngine/resources/asset_data.hpp"

#include "DSCEngine/debug/assert.hpp"

using namespace DSC;

DSC::AssetData::AssetData() : ReadOnlyData(sizeof(DSC::AssetData))  // this line is important
{ }

bool DSC::AssetData::is_bitmap() const { return flags & ROA_IS_BITMAP; }

int DSC::AssetData::get_gfx_length() const
{
	// actual width  = 8*width
	// actual height = 8*height
	// number of pixels = 8*width * 8*height
	//  4bpp = 2   pixels/byte   => len = number of pixels / 2
	//  8bpp = 1   pixel /byte   => len = number of pixels / 1
	// 16bpp = 0.5 pixels/byte   => len = number of pixels * 2
	// condensing last 3 lines   => len = number of pixels * color depth / 8
	return width*height*64 * get_color_depth()/8;
}

void DSC::AssetData::extract_gfx(void* destination) const
{
	extract(destination, 0, get_gfx_length());
}

int DSC::AssetData::get_pal_length() const
{
	// assume gfx_len+pal_len = data_len
	return data_length - get_gfx_length();
}

void DSC::AssetData::extract_palette(void* destination) const
{	
	int gfx_len = get_gfx_length();
	extract(destination, gfx_len, data_length - gfx_len);
}

int DSC::AssetData::get_color_depth() const
{
	int result = (flags & ROA_COLOR_DEPTH)>>9;
	nds_assert(result!=0);
	// result = 1:4bpp, 2:8bpp, 3:16bpp
	return 1<<(result+1); // 4,8 or 16	
}

const int DSC::AssetData::ROA_IS_BITMAP   = (1<<8);
const int DSC::AssetData::ROA_COLOR_DEPTH = (3<<9);