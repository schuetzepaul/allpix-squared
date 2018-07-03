namespace allpix {
    template <typename T>
    void MessageStorage::dispatchMessage(std::shared_ptr<T> message, const std::string& name) {
        static_assert(std::is_base_of<BaseMessage, T>::value, "Dispatched message should inherit from Message class");
        dispatch_message(module_, message, name);
    }

    template <typename T>
    std::shared_ptr<T> MessageStorage::fetchMessage() {
        static_assert(std::is_base_of<BaseMessage, T>::value, "Fetched message should inherit from Message class");
        return std::dynamic_pointer_cast<T>(mpark::get<std::shared_ptr<BaseMessage>>(message_));
    }

    template <typename T>
    std::vector<std::shared_ptr<T>> MessageStorage::fetchMultiMessage() {
        static_assert(std::is_base_of<BaseMessage, T>::value, "Fetched message should inherit from Message class");
        auto base_messages = mpark::get<std::vector<std::shared_ptr<BaseMessage>>>(message_);
        std::vector<std::shared_ptr<T>> derived_messages;
        for (auto& message : base_messages) {
            derived_messages.push_back(std::dynamic_pointer_cast<T>(message));
        }

        return derived_messages;
    }
} // namespace allpix