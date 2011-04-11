#pragma once

using namespace std;

#define buf_family_name(metric_buf) (reinterpret_cast<const wchar_t *>(metric_buf + reinterpret_cast<const UINT>((reinterpret_cast<const OUTLINETEXTMETRICW *>(metric_buf)->otmpFamilyName))))
#define buf_face_name(metric_buf) (reinterpret_cast<const wchar_t *>(metric_buf + reinterpret_cast<const UINT>((reinterpret_cast<const OUTLINETEXTMETRICW *>(metric_buf)->otmpFaceName))))
#define buf_style_name(metric_buf) (reinterpret_cast<const wchar_t *>(metric_buf + reinterpret_cast<const UINT>((reinterpret_cast<const OUTLINETEXTMETRICW *>(metric_buf)->otmpStyleName))))
#define metric_family_name(outline_metric) (reinterpret_cast<const wchar_t *>(reinterpret_cast<const BYTE *>(outline_metric) + reinterpret_cast<const UINT>(outline_metric->otmpFamilyName)))
#define metric_face_name(outline_metric) (reinterpret_cast<const wchar_t *>(reinterpret_cast<const BYTE *>(outline_metric) + reinterpret_cast<const UINT>(outline_metric->otmpFaceName)))
#define metric_style_name(outline_metric) (reinterpret_cast<const wchar_t *>(reinterpret_cast<const BYTE *>(outline_metric) + reinterpret_cast<const UINT>(outline_metric->otmpStyleName)))

class gdipp_font_man
{
	struct font_entry
	{
		HFONT font_handle;
		vector<BYTE> metric_buf;
	};

	map<wstring, font_entry> _font_registry;

	static OUTLINETEXTMETRICW *get_dc_metrics(HDC hdc, vector<BYTE> &metric_buf);
	static unsigned long stream_io(FT_Stream stream, unsigned long offset, unsigned char *buffer, unsigned long count);
	static void stream_close(FT_Stream stream);
	
public:
	void *register_font(const LOGFONTW *attr_buf, DWORD buf_size);
	DWORD get_font_data(void *font_id, DWORD table, DWORD offset, LPVOID data_buf, DWORD buf_size) const;
	const vector<BYTE> *get_font_metrics(void *font_id) const;
	DWORD get_glyph_indices(void *font_id, const wchar_t *str, int count, unsigned short *gi) const;

	FT_Stream lookup_stream(void *font_id) const;
	ULONG lookup_face_index(void *font_id) const;
};