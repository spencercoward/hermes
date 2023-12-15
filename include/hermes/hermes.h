#ifndef HERMES_H
#define HERMES_H

#include <cstdint>

namespace hermes
{

struct Pulse
{
	std::uint64_t m_toa;
	std::uint64_t m_frequency;
	std::uint64_t m_amplitude;
	std::uint64_t m_pulseWidth;
};

} // namespace hermes
#endif // HERMES_H