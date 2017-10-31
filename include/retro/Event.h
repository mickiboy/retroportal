#pragma once

#include <functional>
#include <map>
#include <set>
#include <typeindex>

namespace retro
{
    namespace events
    {
        struct Resize
        {
            int width;
            int height;

            Resize(int width, int height) : width(width), height(height) {}
        };
    }

    template<typename EventType, bool autoRegister = true>
    class Receiver;

    /**
     * Static class for handling application-wide events. Used for registering
     * and unregistering event receivers and for notifying registered receivers.
     */
    class EventManager
    {
    public:
        ~EventManager() {}

        /**
         * Registers an event receiver to a specified event type.
         *
         * @tparam EventType The event struct to listen to
         * @param receiver Pointer to the receiver instance
         */
        template<typename EventType>
        static void registerReceiver(Receiver<EventType>* receiver)
        {
            receivers[typeid(EventType)].insert((void *&&) receiver);
        }

        /**
         * Removes an event receiver from the EventManager to stop notifying it.
         *
         * @tparam EventType The event struct
         * @param receiver Pointer to the receiver instance
         */
        template<typename EventType>
        static void unregisterReceiver(Receiver<EventType>* receiver)
        {
            receivers[typeid(EventType)].erase((void *&&) receiver);
        }

        /**
         * Sends an event to all registered receivers of the specified type.
         *
         * @tparam EventType The event struct
         * @tparam Args 0-n of any argument types
         * @param args 0-n arguments needed for the EventType
         */
        template<typename EventType, typename... Args>
        static void notify(Args... args)
        {
            EventType event = EventType(std::forward<Args>(args)...);

            for (auto receiver : receivers[typeid(EventType)]) {
                reinterpret_cast<Receiver<EventType>*>(receiver)
                    ->receiveEvent(event);
            }
        };

    private:
        EventManager() {}

        static std::map<std::type_index, std::set<void*>> receivers;
    };

    /**
     * Abstract receiver class, which can be inherited to receive the specified
     * event.
     *
     * @tparam EventType The type of the event struct
     * @tparam autoRegister Set to false, if you want to manually
     *         register the receiver to the EventManager
     */
    template<typename EventType, bool autoRegister>
    class Receiver
    {
    public:
        Receiver()
        {
            if (autoRegister) {
                EventManager::registerReceiver<EventType>(this);
            }
        }

        virtual ~Receiver()
        {
            if (autoRegister) {
                EventManager::unregisterReceiver<EventType>(this);
            }
        }

        virtual void receiveEvent(const EventType& event) = 0;
    };
}
