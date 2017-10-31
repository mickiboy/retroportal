#include <retro/Event.h>

namespace retro
{
    std::map<std::type_index, std::set<void*>> EventManager::receivers;
}
