#pragma once

#include "bount-lib/core/api.hpp"

namespace bount::filesystem
{
    /**
     * Can represent a file or directory path.
     * Useful for custom path manipulation.
     */
    class path
    {
    public:
        // Constructors/Destructor functions

        BOUNT_CORE_API ~path() noexcept = default;

        BOUNT_CORE_API path(const path &p_path) noexcept = default;
        BOUNT_CORE_API path &operator=(const path &p_path) noexcept = default;

        BOUNT_CORE_API path(path &&p_path) noexcept = default;
        BOUNT_CORE_API path &operator=(path &&p_path) noexcept = default;

        BOUNT_CORE_API path() noexcept = default;

        BOUNT_CORE_API path(const string &path_str) noexcept;
        BOUNT_CORE_API path &operator=(const string &path_str) noexcept;

        BOUNT_CORE_API path(string &&path_str) noexcept;
        BOUNT_CORE_API path &operator=(string &&path_str) noexcept;

        // Member functions

        BOUNT_CORE_API void append(const path &p_path) noexcept;
        BOUNT_CORE_API [[nodiscard]] path &operator/=(const path &p_path) noexcept;

        BOUNT_CORE_API void concat(const path &p_path) noexcept;
        BOUNT_CORE_API [[nodiscard]] path &operator+=(const path &p_path) noexcept;

        BOUNT_CORE_API [[nodiscard]] bool8 is_absolute() const noexcept;
        BOUNT_CORE_API [[nodiscard]] bool8 is_relative() const noexcept;
        BOUNT_CORE_API [[nodiscard]] bool8 is_file() const noexcept;
        BOUNT_CORE_API [[nodiscard]] bool8 is_dir() const noexcept;
        BOUNT_CORE_API [[nodiscard]] bool8 exists() const noexcept;

        BOUNT_CORE_API [[nodiscard]] path absolute() const noexcept;
        BOUNT_CORE_API [[nodiscard]] path relative(const path &p_path = program_dir()) const noexcept;
        BOUNT_CORE_API [[nodiscard]] path canonical() const noexcept;
        BOUNT_CORE_API [[nodiscard]] path normalize() const noexcept;

        BOUNT_CORE_API [[nodiscard]] bool8 has_filename() const noexcept;
        BOUNT_CORE_API [[nodiscard]] bool8 has_ext() const noexcept;
        BOUNT_CORE_API [[nodiscard]] bool8 has_stem() const noexcept;
        BOUNT_CORE_API [[nodiscard]] bool8 has_parent() const noexcept;

        BOUNT_CORE_API [[nodiscard]] path filename() const noexcept;
        BOUNT_CORE_API [[nodiscard]] path ext() const noexcept;
        BOUNT_CORE_API [[nodiscard]] path stem() const noexcept;
        BOUNT_CORE_API [[nodiscard]] path parent() const noexcept;

        /** @return The string of the path. */
        BOUNT_CORE_API [[nodiscard]] string to_string() const noexcept;

        // Non-member functions

        BOUNT_CORE_API friend path operator/(const path &lhs, const path &rhs) noexcept;
        BOUNT_CORE_API friend path operator+(const path &lhs, const path &rhs) noexcept;

        /** @return Path to the program's executable. */
        BOUNT_CORE_API [[nodiscard]] static const path &program_file() noexcept;
        /** @return Path to the program's directory. */
        BOUNT_CORE_API [[nodiscard]] static const path &program_dir() noexcept;

        /** @return Path to the system's temp directory. */
        BOUNT_CORE_API [[nodiscard]] static const path &temp_dir() noexcept;

    private:
        string m_path_str;
    };
}