#pragma once

#include <iostream>
#include <chrono>

/**
 * @brief Minimalistischer Logger.
 *
 * + out() schreibt nach std::cout
 * + err() schreibt nach std::cerr
 * + debug() schreibt nach std::cout, wenn via Debug kompiliert.
 *
 * @example
 * Log::info() << "Mein " << 2 << ". Wagen sind " << 10 << " U-Boote.\n" << Log::flush;
 */
namespace nada {
class Log final {

    enum Level {
        LOG_INFO,
        LOG_DEBUG,
        LOG_ERROR
    };

    explicit Log(Level level) : level(level) {}

    const Level level;

    static inline std::ostream* out_stream = &std::cout;

public:

    /// Hilfselement zum flushen.
    struct Flush {};

    /// Hilfselement zum \n + flushen.
    struct Endl {};

    /// Hilfselement zum flushen.
    static const inline Flush flush;

    /// Hilfselement zum \n + flushen.
    static const inline Endl endl;

    /// Schreibt nach std::cout bei Debug-Builds.
    static const Log& debug() noexcept {
        thread_local const Log log(LOG_DEBUG);
        return log;
    }

    /// Schreibt nach std::cerr.
    static const Log& err() noexcept {
        thread_local const Log log(LOG_ERROR);
        return log;
    }

    /// Schreibt nach std::cout.
    static const Log& out() noexcept {
        thread_local const Log log(LOG_INFO);
        return log;
    }

    /**
     * Gibt die Dauer des Funktionsaufrufs aus (nur im Debug-Modus).
     * Im Release-Modus wird einfach die Funktion ausgeführt.
     */
    template <typename T>
    static void benchmark_debug(T&& funktion, const std::string& text) {
        #ifndef NDEBUG
            benchmark(funktion, text);
        #else
            funktion();
        #endif
    }

    /// Gibt die Dauer des Funktionsaufrufs aus (immer).
    template <typename T>
    static void benchmark(T&& funktion, const std::string& text) {
        const auto start = std::chrono::system_clock::now();
        funktion();
        const auto ende = std::chrono::system_clock::now();
        const std::chrono::duration<double> dauer = ende - start;
        *out_stream << text << " Dauer: " << dauer.count() << "s\n";
    }

    /**
     * 
     **/
    static void set_output(std::ostream* stream) { out_stream = stream; }

    /**
     * 
     */
    static void to_cout() { out_stream = &std::cout; }

    /// Flush.
    const Log& operator<<(const Flush& f) const noexcept {
        (void) f;
        switch (level) {
            case LOG_INFO:
                *out_stream << std::flush;
                break;
            case LOG_ERROR:
                *out_stream << std::flush;
                break;
            case LOG_DEBUG:
                #ifndef NDEBUG
                *out_stream << std::flush;
                #endif
                break;
        }
        return *this;
    }

    /// Newline + Flush.
    const Log& operator<<(const Endl& e) const noexcept {
        (void) e;
        switch (level) {
            case LOG_INFO:
                *out_stream << std::endl;
                break;
            case LOG_ERROR:
                *out_stream << std::endl;
                break;
            case LOG_DEBUG:
                #ifndef NDEBUG
                *out_stream << std::endl;
                #endif
                break;
        }
        return *this;
    }

    /// Generische Ausgabe in die Konsole.
    template<typename T>
    const Log& operator<<(const T& item) const noexcept {
        switch (level) {
            case LOG_INFO:
                *out_stream << item;
                break;
            case LOG_ERROR:
                *out_stream << item;
                break;
            case LOG_DEBUG:
                #ifndef NDEBUG
                *out_stream << item;
                #endif
                break;
        }
        return *this;
    }

};
}
