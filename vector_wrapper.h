#include "datastructure.h"

namespace cpt323::vector
{
    class vector_wrapper: public datastructure::datastructure
    {
        // Inner vector that this class wraps
        std::vector<std::string> inner_vector;

        class vector_iterator: public datastructure::datastructure::iterator
        {
            // Vector iterator that this class wraps
            std::vector<std::string>::iterator inner;
        public:
            vector_iterator(std::vector<std::string>::iterator iter) : inner(iter)
            {
            }
            // Overridden methods
            const std::string& operator*(void) const override;
            std::unique_ptr<iterator> operator++(void) override;
            std::unique_ptr<iterator> operator++(int) override;
            bool operator==(const iterator&) override;
            bool operator!=(const iterator&) override;
            virtual ~vector_iterator()
            {
            }
        };
    public:
        vector_wrapper()
        {
        }
        // Overridden methods
        void add(const std::string&) override;
        std::unique_ptr<iterator> begin(void) override;
        std::unique_ptr<iterator> end(void) override;
        std::size_t size(void) override;
        void sort(void) override;
        bool empty(void) override;
        virtual ~vector_wrapper()
        {
        }
    };
}