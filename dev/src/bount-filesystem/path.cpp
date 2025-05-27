#include "bount-lib/core/precompiled.hpp"
#include "bount-filesystem/path.hpp"

#if defined(BOUNT_WINDOWS_OS)
#include <windows.h> // For GetModuleFileNameA
#elif defined(BOUNT_LINUX_OS)
#include <limits.h> // For PATH_MAX
#include <unistd.h> // For readlink
#endif

#include <mutex>

namespace bount::filesystem
{
    path::path(const string &p_path_str) noexcept
        : m_path_str(p_path_str)
    {
    }
    path::path(string &&p_path_str) noexcept
        : m_path_str(std::move(p_path_str))
    {
    }

    void path::append(const path &p_path) noexcept
    {
        m_path_str += string("/") + p_path.m_path_str;
    }
    path &path::operator/=(const path &p_path) noexcept
    {
        m_path_str += string("/") + p_path.m_path_str;
        return *this;
    }

    void path::concat(const path &p_path) noexcept
    {
        m_path_str += p_path.m_path_str;
    }
    path &path::operator+=(const path &p_path) noexcept
    {
        m_path_str += p_path.m_path_str;
        return *this;
    }

    bool8 path::is_absolute() const noexcept
    {
        return false;
    }
    bool8 path::is_relative() const noexcept
    {
        return false;
    }
    bool8 path::is_file() const noexcept
    {
        return false;
    }
    bool8 path::is_dir() const noexcept
    {
        return false;
    }
    bool8 path::exists() const noexcept
    {
        return false;
    }

    path path::absolute() const noexcept
    {
        return path("");
    }
    path path::relative(const path &p_path) const noexcept
    {
        return path("");
    }
    path path::canonical() const noexcept
    {
        return path("");
    }
    path path::normalize() const noexcept
    {
        return path("");
    }

    bool8 path::has_filename() const noexcept
    {
        return false;
    }
    bool8 path::has_ext() const noexcept
    {
        return false;
    }
    bool8 path::has_stem() const noexcept
    {
        return false;
    }
    bool8 path::has_parent() const noexcept
    {
        return false;
    }

    path path::filename() const noexcept
    {
        return path("");
    }
    path path::ext() const noexcept
    {
        return path("");
    }
    path path::stem() const noexcept
    {
        return path("");
    }
    path path::parent() const noexcept
    {
        const auto it = std::find_if(m_path_str.rbegin(), m_path_str.rend(), [](auto c) { return c == '\\' || c == '/'; });
        const auto dist = std::distance(it, m_path_str.rend()) - 1; // The -1 excludes the slash.
        return m_path_str.substr(0, dist);
    }

    string path::to_string() const noexcept
    {
        return m_path_str;
    }

    path operator/(const path &lhs, const path &rhs) noexcept
    {
        return lhs.m_path_str + '/' + rhs.m_path_str;
    }
    path operator+(const path &lhs, const path &rhs) noexcept
    {
        return lhs.m_path_str + rhs.m_path_str;
    }

    const path &path::program_file() noexcept
    {
        static path program_file_path;
        static std::once_flag once;
        std::call_once(once, []()
        {
        #if defined(BOUNT_WINDOWS_OS)
            char buffer[MAX_PATH];
            GetModuleFileNameA(NULL, buffer, MAX_PATH);
        #elif defined(BOUNT_LINUX_OS)
            char buffer[PATH_MAX];
            ssize_t count = readlink("/proc/self/exe", buffer, PATH_MAX);
        #else
            #error "Not implemented for the current os"
        #endif
            program_file_path.m_path_str = buffer;
        });
        return program_file_path;
    }
    const path &path::program_dir() noexcept
    {
        static path program_dir_path;
        static std::once_flag once;
        std::call_once(once, []() { program_dir_path = program_file().parent(); });
        return program_dir_path;
    }
    const path &path::program_tmp_dir() noexcept
    {
        static path p("");
        return p;
    }
}