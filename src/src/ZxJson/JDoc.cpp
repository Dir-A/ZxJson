#include <ZxJson/JDoc.h>
#include <ZxJson/Platform.h>


namespace ZQF::ZxJson
{
    JDoc::JDoc()
    {
    }

    JDoc::JDoc(const std::string_view msPath)
    {
        this->LoadViaFile(msPath);
    }

    JDoc::~JDoc()
    {
    }

    auto JDoc::GetJValue() -> JValue&
    {
        return m_JValue;
    }

    auto JDoc::GetJArray() -> JArray_t&
    {
        return m_JValue.ToArray();
    }

    auto JDoc::GetJObject() -> JObject_t&
    {
        return m_JValue.ToObject();
    }

    auto JDoc::LoadViaMemory(std::span<char> spData) -> bool
    {
        return JParser{ spData }.Parse(m_JValue);
    }

    auto JDoc::LoadViaFile(const std::string_view msPath) -> bool
    {
        auto [file_size, file_data] = Private::ReadAllBytes(msPath);
        return this->LoadViaMemory(std::span{ file_data.get(), file_size });
    }

    auto JDoc::StoreViaMemory(bool isFormat) const -> std::string
    {
        return m_JValue.Dump(isFormat);
    }

    auto JDoc::StoreViaFile(const std::string_view msPath, const bool isFormat, const bool isForceSave) const -> void
    {
        auto json_str = this->StoreViaMemory(isFormat);
        Private::WriteAllBytes(msPath, std::span{ json_str }, isForceSave);
    }
} // namespace ZQF::ZxJson