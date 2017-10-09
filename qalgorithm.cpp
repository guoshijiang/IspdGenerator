#include "qalgorithm.h"

QAlgorithm::QAlgorithm()
{

}

QAlgorithm::~QAlgorithm()
{

}

QString QAlgorithm::encrypt_ispd_id(unsigned int id)
{
    QString q_str;
    std::string str;
    do
    {
        unsigned int mod = id % 34;
        str += g_ispd_id_map_table[mod];
        id = id / 34;
    }
    while(0 != id);
    std::reverse(str.begin(), str.end());
    q_str = QString::fromStdString(str);
    return q_str;
}

unsigned int QAlgorithm::dencrypt_ispd_id(const std::string& id)
{
    unsigned int rtn = 0;
    size_t size = id.size();
    assert(0 != size);

    for (size_t i = size; i > 0; --i)
    {
        unsigned int j = 0;
        for(; j < 34; j++)
        {
            if (id[i-1] == g_ispd_id_map_table[j])
            break;
        }
        assert(34 != j);
        rtn += j * pow(34, size-i);
    }
    return rtn;
}

#if 0
int main( int argc, char* argv[] )
{
    unsigned int start = 10000;
    unsigned int count = 1000000;

    char psztemp[64] = {0};

    for ( unsigned int i = start; i < start + count; ++i )
    {
        snprintf( psztemp, 64, "%u", i );
        assert( 0 != strlen(psztemp) );
        unsigned int base = pow( 10, strlen(psztemp) ) *  100;

        std::string str = encrypt_ispd_id( i+base );
        unsigned int rtn = dencrypt_ispd_id( str );
        std::cout << "Encrypt " << i+base << " : " << str << " and " << rtn << std::endl;
        assert( i+base == rtn );
    }
}
#endif

