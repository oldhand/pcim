//author: linyuanxuan
//multipart byte ranges parser
#ifndef _MultipartByteRangesParser_H
#define _MultipartByteRangesParser_H

#include "Defines.h"
#include "DownloadTaskImpl.h"

DOWNLOAD_MANAGER_START

enum ParseState
{
	START,
	START_BOUNARY,
	HEADERS_FIELD_START,
	HEADERS_FIELD,
	HEADERS_ALMOST_DONE,
	HEADER_VALUE_START,
	HEADER_VALUE,
	HEADER_VALUE_ALMOST_DONE,
	PART_DATA_START,
	PART_DATA,
	PART_DATA_ALMOST_BOUNDARY,
	END
};

struct RangeDescribe
{
	int _fd;
	int _iOffset;
};

class MultipartByteRangesParser
{
public:
	MultipartByteRangesParser();
	~MultipartByteRangesParser();

	friend class DownloadTaskImpl;

	void MultipartParserExecute(const char *pBuffer, size_t iSize, const std::string& rBoundary, FILE *f, DownloadTaskImpl* pTaskImpl);
	void AnalyzeRangeBuffers(const std::string& rFileName);

	//use when a download task is unexpected interrupted.
	//make ranges string that hasn't been downloaded like("2-3, 4-10...")
	std::string MakeUndownloadRanges(std::vector<DownLoadRange>& rExceptRanges, const std::string& rFileName);

	inline const RangeDescribe& GetRangeBuffer(const std::string& rRange)
	{
		return _multiRangeDataMap[rRange];
	}

	void Reset();
private:	
	//range string, range buffer offsets
	std::map<std::string, RangeDescribe> _multiRangeDataMap;
	ParseState _eState;
	size_t _iDounaryIndex;
	uint64_t _iPrevToByte;
	uint64_t _iDataSize;
};

DOWNLOAD_MANAGER_END

#endif
