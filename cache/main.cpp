#include <iostream>
#include <list>
#include <unordered_map>
#include <iterator>

enum Errors{
    OK = 0,
    ERROR_CACHE_OR_LINE_LENGTH = 1,
};

class cache{
    private:
    size_t length;
    std::list <int> data;
    std::unordered_map <int, std::list<int>::iterator> hash;
    //std::unordered_map <int> hash;

    public:
    cache(int len)
    {
        length = len;
    }

    bool full()
    {
        return hash.size() >= length;
    }

    unsigned lookup_update(int* elems, unsigned count_elems = 1)
    {
        unsigned num_hits = 0;

        for(unsigned i = 0; i < count_elems; i++)
            std::cout << elems[i] << std::endl;

        for(unsigned i = 0; i < count_elems; i++)
        {
            auto hit = hash.find(elems[i]);

            /*std::cout << hit->first << std::endl;
            std::cout << hash.end()->first << std::endl;*/

            if(hit == hash.end())
            {
                if(full())
                {
                    hash.erase(data.back());
                    data.pop_back();
                }

                data.push_front(elems[i]);
                hash[elems[i]] = data.begin();

                continue;
            }

            num_hits++;

            for(std::list<int>::iterator iter = data.begin(); iter != data.end(); iter++)
            {
                if(iter == hit->second)
                {
                    data.erase(iter);
                    break;
                }
            }

            data.push_front(elems[i]);
        }

        return num_hits;
    }
};

bool read_cache_line_lengths(int *const cache_length, int *const line_length);
bool read_line(int *const line_length, int* line);

int main()
{
    int error = 0;

    int cache_length = 0;
    int line_length = 0;

    if(!read_cache_line_lengths(&cache_length, &line_length))
        return error;

    cache cache{cache_length};

    int* line = new int[line_length];
    read_line(&line_length, line);

    unsigned hit = cache.lookup_update(line, line_length);
    std::cout << "Hits: " << hit << std::endl;

    delete[] line;
    return error;
}

bool read_cache_line_lengths(int *const cache_length, int *const line_length)
{
    std::cin >> *cache_length >> *line_length;

    std::cout << "cache_length: " << *cache_length << std::endl;
    std::cout << "line_length: " << *line_length << std::endl;

    return true;
}

bool read_line(int *const line_length, int* line)
{
    for(int i = 0; i < *line_length; i++)
        std::cin >> line[i];

    return true;
}
