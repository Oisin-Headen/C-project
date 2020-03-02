#include "datastructure.h"

namespace cpt323::set
{
    class set_wrapper: public datastructure::datastructure
    {
        // The inner multiset that this class wraps.
        std::multiset<std::string> inner_set;

        class set_iterator: public datastructure::datastructure::iterator
        {
            // The multiset iterator that this class wraps.
            std::multiset<std::string>::iterator inner;
        public:
            set_iterator(std::multiset<std::string>::iterator iter) : inner(iter)
            {
            }
            // Overriden functions
            const std::string& operator*(void) const override;
            std::unique_ptr<iterator> operator++(void) override;
            std::unique_ptr<iterator> operator++(int) override;
            bool operator==(const iterator&) override;
            bool operator!=(const iterator&) override;
            virtual ~set_iterator()
            {
            }
        };
    public:
        set_wrapper()
        {
        }
        // Overriden functions
        void add(const std::string&) override;
        std::unique_ptr<iterator> begin(void) override;
        std::unique_ptr<iterator> end(void) override;
        std::size_t size(void) override;
        void sort(void) override;
        bool empty(void) override;
        virtual ~set_wrapper()
        {
        }
    };
}