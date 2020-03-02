#include "datastructure.h"

namespace cpt323::stdlist
{
    class stdlist_wrapper: public datastructure::datastructure
    {
        // The inner list this class wraps.
        std::list<std::string> inner;

        class stdlist_iterator: public datastructure::datastructure::iterator
        {
            // The inner iterator this class wraps.
            std::list<std::string>::iterator inner;
        public:
            stdlist_iterator(std::list<std::string>::iterator iter) : inner(iter)
            {
            }
            // Overridden methods.
            const std::string& operator*(void) const override;
            std::unique_ptr<iterator> operator++(void) override;
            std::unique_ptr<iterator> operator++(int) override;
            bool operator==(const iterator&) override;
            bool operator!=(const iterator&) override;
            virtual ~stdlist_iterator()
            {
            }
        };
    public:
        stdlist_wrapper()
        {
        }
        // Overridden methods.
        void add(const std::string&) override;
        std::unique_ptr<iterator> begin(void) override;
        std::unique_ptr<iterator> end(void) override;
        std::size_t size(void) override;
        void sort(void) override;
        bool empty(void) override;
        virtual ~stdlist_wrapper()
        {
        }
    };
}