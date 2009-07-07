#pragma once

#include "DownloadComponentInfo.h"

class IDownloadCallback
{
public:
	virtual void Status(ULONG progress_current, ULONG progress_max, const std::wstring& description) = 0;
	virtual void DownloadComplete() = 0;
	virtual void DownloadError(const std::wstring& message) = 0;
	virtual bool IsDownloadCancelled() const = 0;
	virtual void DownloadCancel() = 0;
	virtual const std::vector<DownloadComponentInfo>& GetComponents() const = 0;
};
