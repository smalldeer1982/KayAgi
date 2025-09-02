# A+B  A-B  A*B  A/B A%B Problem

## 题目背景

这个题目很新颖吧！！！


## 题目描述

求 $A$ 与 $B$ 的和、差、积、商、余。

**由于数据有修改，减法运算结果可能带负号**

## 说明/提示

$|A|,|B| \leq 10^4$，这里表示数字的位数而不是绝对值

$ A,B > 0 $


## 样例 #1

### 输入

```
1
1```

### 输出

```
2
0
1
1
0```

# 题解

## 作者：MashPlant (赞：255)

更新一次~~

看到好多人卡到我前面去了，心情复杂，于是又写了一个更快一点的。现在16ms，还是第一。没有用vector，用起来的确有点麻烦。

除法的实现方法改了一下，改成每一个1e9之内二分答案，这样复杂度还是O(n^2)，但是常数小了很多。
```cpp
// luogu-judger-enable-o2
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cassert>

typedef int i32;
typedef unsigned u32;
typedef unsigned long long u64;

struct BigInt
{
    const static u32 exp = 9;
    const static u32 mod = 1000000000;

    static i32 abs_comp(const BigInt &lhs, const BigInt &rhs)
    {
        if (lhs.len != rhs.len)
            return lhs.len < rhs.len ? -1 : 1;
        for (u32 i = lhs.len - 1; ~i; --i)
            if (lhs.val[i] != rhs.val[i])
                return lhs.val[i] < rhs.val[i] ? -1 : 1;
        return 0;
    }

    u32 *val, len, sgn;

    BigInt(u32 *val = nullptr, u32 len = 0, u32 sgn = 0) : val(val), len(len), sgn(sgn) {}

    // copy_to cannot guarantee val[x] == 0 for x >= len
    // other function should set (the position they assume to be zero) as zero
    void copy_to(BigInt &dst) const
    {
        dst.len = len, dst.sgn = sgn;
        memcpy(dst.val, val, sizeof(u32) * len);
    }

    void trim()
    {
        while (len && !val[len - 1])
            --len;
        if (len == 0)
            sgn = 0;
    }

    void add(BigInt &x)
    {
        if (sgn ^ x.sgn)
            return x.sgn ^= 1, sub(x);
        val[len = std::max(len, x.len)] = 0;
        for (u32 i = 0; i < x.len; ++i)
            if ((val[i] += x.val[i]) >= mod)
                val[i] -= mod, ++val[i + 1];
        for (u32 i = x.len; i < len && val[i] >= mod; ++i)
            val[i] -= mod, ++val[i + 1];
        if (val[len])
            ++len;
    }

    void sub(BigInt &x)
    {
        if (sgn ^ x.sgn)
            return x.sgn ^= 1, add(x);
        if (abs_comp(*this, x) < 0)
            std::swap(*this, x), sgn ^= 1;
        val[len] = 0;
        for (u32 i = 0; i < x.len; ++i)
            if ((val[i] -= x.val[i]) & 0x80000000)
                val[i] += mod, --val[i + 1];
        for (u32 i = x.len; i < len && val[i] & 0x80000000; ++i)
            val[i] += mod, --val[i + 1];
        trim();
    }

    void mul(BigInt &x, u32 *ext_mem)
    {
        assert(this != &x);
        memcpy(ext_mem, val, sizeof(u32) * len);
        memset(val, 0, sizeof(u32) * (len + x.len));
        for (u32 i = 0; i < len; ++i)
            for (u32 j = 0; j < x.len; ++j)
            {
                u64 tmp = (u64)ext_mem[i] * x.val[j] + val[i + j];
                val[i + j] = tmp % mod;
                val[i + j + 1] += tmp / mod;
            }
        len += x.len, sgn ^= x.sgn;
        trim();
    }

    void mul(u32 x)
    {
        if (x & 0x80000000)
            x = -x, sgn ^= 1;
        u64 carry = 0;
        for (u32 i = 0; i < len; ++i)
        {
            carry += (u64)val[i] * x;
            val[i] = carry % mod;
            carry /= mod;
        }
        if (carry)
            val[len++] = carry;
        trim();
    }

    void div(BigInt &x, BigInt &remainder, u32 *ext_mem)
    {
        assert(this != &x && this != &remainder);
        copy_to(remainder), memset(val, 0, sizeof(u32) * len);
        u32 shift = len - x.len;
        if (shift & 0x80000000)
            return void(len = sgn = 0);
        while (~shift)
        {
            u32 l = 0, r = mod;
            BigInt mul_test{ext_mem}, remainder_high{remainder.val + shift, remainder.len - shift};
            while (l <= r)
            {
                u32 mid = (l + r) / 2;
                x.copy_to(mul_test), mul_test.mul(mid);
                abs_comp(mul_test, remainder_high) < 0 ? l = mid + 1 : r = mid - 1;
            }
            val[shift] = r;
            x.copy_to(mul_test), mul_test.mul(r);
            remainder_high.sub(mul_test), remainder.trim();
            --shift;
        }
        sgn ^= x.sgn;
        trim();
    }

    void div(u32 x)
    {
        if (x & 0x80000000)
            x = -x, sgn ^= 1;
        u64 carry = 0;
        for (u32 i = len - 1; ~i; --i)
        {
            carry = carry * mod + val[i];
            val[i] = carry / x;
            carry %= x;
        }
        trim();
    }

    void read(const char *s)
    {
        sgn = len = 0;
        i32 bound = 0, pos;
        if (s[0] == '-')
            sgn = bound = 1;
        u64 cur = 0, pow = 1;
        for (pos = strlen(s) - 1; pos + 1 >= exp + bound; pos -= exp, val[len++] = cur, cur = 0, pow = 1)
            for (i32 i = pos; i + exp > pos; --i)
                cur += (s[i] - '0') * pow, pow *= 10;
        for (cur = 0, pow = 1; pos >= bound; --pos)
            cur += (s[pos] - '0') * pow, pow *= 10;
        if (cur)
            val[len++] = cur;
    }

    void print()
    {
        if (len)
        {
            if (sgn)
                putchar('-');
            printf("%u", val[len - 1]);
            for (u32 i = len - 2; ~i; --i)
                printf("%0*u", exp, val[i]);
        }
        else
            putchar('0');
        puts("");
    }
};

const int N = 1e4 + 20;
u32 a_[N], b_[N], r_[N], tmp[N * 2];
char sa[N], sb[N];

int main()
{
    scanf("%s%s", sa, sb);
    {
        BigInt a{a_}, b{b_};
        a.read(sa), b.read(sb), a.add(b), a.print();
    }
    {
        BigInt a{a_}, b{b_};
        a.read(sa), b.read(sb), a.sub(b), a.print();
    }
    {
        BigInt a{a_}, b{b_};
        a.read(sa), b.read(sb), a.mul(b, tmp), a.print();
    }
    {
        BigInt a{a_}, b{b_}, r{r_};
        a.read(sa), b.read(sb), a.div(b, r, tmp), a.print();
        r.print();
    }
}
```
--------------------------------------

各位C++大佬，速度比不过python你们的心不会痛吗?

76ms，目前第一，干掉python，算是维护一下C++的尊严吧。

除法的思路是倍增，记n为输入串的长度(而非输入串代表的数值大小)，则倍增的判断次数是O(n)，每次判断只涉及到加法，复杂度也是O(n)，总体O(n^2)。二分查找的话，每次判断都是乘法，总体复杂度O(n^3)。

```cpp
// luogu-judger-enable-o2
#include <bits/stdc++.h>
class BigInt
{
#define Value(x, nega) ((nega) ? -(x) : (x))
#define At(vec, index) ((index) < vec.size() ? vec[(index)] : 0)
    //C风格的比较函数,其正负等于abs(lhs)-abs(rhs)的正负
    static int absComp(const BigInt &lhs, const BigInt &rhs)
    {
        if (lhs.size() != rhs.size())
            return lhs.size() < rhs.size() ? -1 : 1;
        for (int i = lhs.size() - 1; i >= 0; --i)
            if (lhs[i] != rhs[i])
                return lhs[i] < rhs[i] ? -1 : 1;
        return 0;
    }
    using Long = long long;
    const static int Exp = 9;
    const static Long Mod = 1000000000;
    mutable std::vector<Long> val;
    mutable bool nega = false;
    //规定:0的nega必须是false,0的size必须是0
    void trim() const
    {
        while (val.size() && val.back() == 0)
            val.pop_back();
        if (val.empty())
            nega = false;
    }
    int size() const { return val.size(); }
    Long &operator[](int index) const { return val[index]; }
    Long &back() const { return val.back(); }
    BigInt(int size, bool nega) : val(size), nega(nega) {}
    BigInt(const std::vector<Long> &val, bool nega) : val(val), nega(nega) {}

  public:
    friend std::ostream &operator<<(std::ostream &os, const BigInt &n)
    {
        if (n.size())
        {
            if (n.nega)
                putchar('-');
            for (int i = n.size() - 1; i >= 0; --i)
            {
                if (i == n.size() - 1)
                    printf("%lld", n[i]); 
                else
                    printf("%0*lld", n.Exp, n[i]); 
            }
        }
        else
            putchar('0');
        return os;
    }
    friend BigInt operator+(const BigInt &lhs, const BigInt &rhs)
    {
        BigInt ret(lhs);
        return ret += rhs;
    }
    friend BigInt operator-(const BigInt &lhs, const BigInt &rhs)
    {
        BigInt ret(lhs);
        return ret -= rhs;
    }
    BigInt(Long x = 0)
    {
        if (x < 0)
            x = -x, nega = true;
        while (x >= Mod)
            val.push_back(x % Mod), x /= Mod;
        if (x)
            val.push_back(x);
    }
    BigInt(const char *s)
    {
        int bound = 0, pos;
        if (s[0] == '-')
            nega = true, bound = 1;
        Long cur = 0, pow = 1;
        for (pos = strlen(s) - 1; pos >= Exp + bound - 1; pos -= Exp, val.push_back(cur), cur = 0, pow = 1)
            for (int i = pos; i > pos - Exp; --i)
                cur += (s[i] - '0') * pow, pow *= 10;
        for (cur = 0, pow = 1; pos >= bound; --pos)
            cur += (s[pos] - '0') * pow, pow *= 10;
        if (cur)
            val.push_back(cur);
    }
    BigInt &operator+=(const BigInt &rhs)
    {
        const int cap = std::max(size(), rhs.size()) + 1;
        val.resize(cap);
        int carry = 0;
        for (int i = 0; i < cap - 1; ++i)
        {
            val[i] = Value(val[i], nega) + Value(At(rhs, i), rhs.nega) + carry, carry = 0;
            if (val[i] >= Mod)
                val[i] -= Mod, carry = 1; //至多只需要减一次，不需要取模
            else if (val[i] < 0)
                val[i] += Mod, carry = -1; //同理
        }
        if ((val.back() = carry) == -1) //assert(val.back() == 1 or 0 or -1)
        {
            nega = true, val.pop_back();
            bool tailZero = true;
            for (int i = 0; i < cap - 1; ++i)
            {
                if (tailZero && val[i])
                    val[i] = Mod - val[i], tailZero = false;
                else
                    val[i] = Mod - 1 - val[i];
            }
        }
        trim();
        return *this;
    }
    friend BigInt operator-(const BigInt &rhs)
    {
        BigInt ret(rhs);
        ret.nega ^= 1;
        return ret;
    }
    BigInt &operator-=(const BigInt &rhs)
    {
        rhs.nega ^= 1;
        *this += rhs;
        rhs.nega ^= 1;
        return *this;
    }
    //高精*高精没办法原地操作，所以实现operator*
    //高精*低精可以原地操作，所以operator*=
    friend BigInt operator*(const BigInt &lhs, const BigInt &rhs)
    {
        const int cap = lhs.size() + rhs.size() + 1;
        BigInt ret(cap, lhs.nega ^ rhs.nega);
        //j < l.size(),i - j < rhs.size() => i - rhs.size() + 1 <= j
        for (int i = 0; i < cap - 1; ++i) // assert(0 <= ret[cap-1] < Mod)
            for (int j = std::max(i - rhs.size() + 1, 0), up = std::min(i + 1, lhs.size()); j < up; ++j)
            {
                ret[i] += lhs[j] * rhs[i - j];
                ret[i + 1] += ret[i] / Mod, ret[i] %= Mod;
            }
        ret.trim();
        return ret;
    }
    BigInt &operator*=(const BigInt &rhs) { return *this = *this * rhs; }
    friend BigInt operator/(const BigInt &lhs, const BigInt &rhs)
    {
        static std::vector<BigInt> powTwo{BigInt(1)};
        static std::vector<BigInt> estimate;
        estimate.clear();
        if (absComp(lhs, rhs) < 0)
            return BigInt();
        BigInt cur = rhs;
        int cmp;
        while ((cmp = absComp(cur, lhs)) <= 0)
        {
            estimate.push_back(cur), cur += cur;
            if (estimate.size() >= powTwo.size())
                powTwo.push_back(powTwo.back() + powTwo.back());
        }
        if (cmp == 0)
            return BigInt(powTwo.back().val, lhs.nega ^ rhs.nega);
        BigInt ret = powTwo[estimate.size() - 1];
        cur = estimate[estimate.size() - 1];
        for (int i = estimate.size() - 1; i >= 0 && cmp != 0; --i)
            if ((cmp = absComp(cur + estimate[i], lhs)) <= 0)
                cur += estimate[i], ret += powTwo[i];
        ret.nega = lhs.nega ^ rhs.nega;
        return ret;
    }
    bool operator==(const BigInt &rhs) const
    {
        return nega == rhs.nega && val == rhs.val;
    }
    bool operator!=(const BigInt &rhs) const { return nega != rhs.nega || val != rhs.val; }
    bool operator>=(const BigInt &rhs) const { return !(*this < rhs); }
    bool operator>(const BigInt &rhs) const { return !(*this <= rhs); }
    bool operator<=(const BigInt &rhs) const
    {
        if (nega && !rhs.nega)
            return true;
        if (!nega && rhs.nega)
            return false;
        int cmp = absComp(*this, rhs);
        return nega ? cmp >= 0 : cmp <= 0;
    }
    bool operator<(const BigInt &rhs) const
    {
        if (nega && !rhs.nega)
            return true;
        if (!nega && rhs.nega)
            return false;
        return (absComp(*this, rhs) < 0) ^ nega;
    }
    void swap(const BigInt &rhs) const
    {
        std::swap(val, rhs.val);
        std::swap(nega, rhs.nega);
    }
};
const int N = 1e4 + 10;
char a[N], b[N];
int main()
{
    scanf("%s%s", a, b);
    BigInt ba(a), bb(b);
    std::cout << ba + bb << '\n';
    std::cout << ba - bb << '\n';
    std::cout << ba * bb << '\n';
    BigInt d;
    std::cout << (d = ba / bb) << '\n';
    std::cout << ba - d * bb << '\n';
    return 0;
}
```

---

## 作者：我是PG (赞：111)

~~难道我谷这么多大佬没有人知道bc吗？~~

自从蒟蒻了解了bc，就像哥伦布发现新大陆，赶紧就用它来水高精模板题了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    char a[100000],b[100000],c[100000];
    scanf("%s%s",a,b);
    sprintf(c,"echo %s+%s | bc | tr '\n' ' ' | tr '\\' ' ' | sed 's/ //g'",a,b);
    system(c);
    cout<<endl;
    sprintf(c,"echo %s-%s | bc | tr '\n' ' ' | tr '\\' ' ' | sed 's/ //g'",a,b);
    system(c);
    cout<<endl;
    sprintf(c,"echo %s*%s | bc | tr '\n' ' ' | tr '\\' ' ' | sed 's/ //g'",a,b);
    system(c);
    cout<<endl;
    sprintf(c,"echo %s/%s | bc | tr '\n' ' ' | tr '\\' ' ' | sed 's/ //g'",a,b);
    system(c);
    cout<<endl;
    sprintf(c,"echo %s %% %s | bc | tr '\n' ' ' | tr '\\' ' ' | sed 's/ //g'",a,b);
    system(c);
    cout<<endl;
    return 0;
}
```

但是这个做法有一个很大的缺陷，就是不能把计算的结果用一个变量（字符数组）保存，而是只能直接输出。这就直接导致这种做法只能水高精度的模板题，而不是模板的高精度题是很难使用这个方法的

虽然有这个局限，但也能让C党20行切掉高精度，享受Python的快感！

对了，如果有哪个大佬知道如何将高精度的运算结果保存下来麻烦私信我，谢谢

---

## 作者：BillYang (赞：62)

楼下的题解都在坑我呢，怎么交上去都40分？

没办法自己写一个。

高精度模板只能得90分TLE，速度太慢，亿进制优化要开long long反而更慢，只有80分。

第十个点数据下下来发现除法过于slow，用了10s，想个办法优化除法？

发现while循环中一直在做高精度减法，这样会使效率变得异常低，怎么办呢？

我们用倍增来减少高精度减法的次数，预处理出log2(1e)内的2的幂，然后倍增出解。

附代码：

```cpp
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<cstdio>
#include<cmath>
#include<ctime>
using namespace std;
inline const int Get_Int() {
    int num=0,bj=1;
    char x=getchar();
    while(x<'0'||x>'9') {
        if(x=='-')bj=-1;
        x=getchar();
    }
    while(x>='0'&&x<='9') {
        num=num*10+x-'0';
        x=getchar();
    }
    return num*bj;
}
struct BigInteger {
    static const int BASE=100000000; //高进制
    static const int WIDTH=8; //高进制位数
    vector<long long>s;
    BigInteger() { //构造函数：初始赋0
        *this=0;
    }
    BigInteger(const int& num) { // 构造函数
        *this=num;
    }
    //赋值
    BigInteger operator = (int num) {
        s.clear();
        do {
            s.push_back(num%BASE);
            num/=BASE;
        } while(num>0);
        return *this;
    }
    BigInteger operator = (const string& str) {
        s.clear();
        int x,len=(str.length()-1)/WIDTH+1;
        for(int i=0; i<len; i++) {
            int end=str.length()-i*WIDTH;
            int start=max(0,end-WIDTH);
            sscanf(str.substr(start,end-start).c_str(),"%lld",&x);
            s.push_back(x);
        }
        return *this;
    }
    //比较
    bool operator < (const BigInteger& b) {
        if(s.size()<b.s.size())return true;
        if(s.size()>b.s.size())return false;
        for(int i=s.size()-1; i>=0; i--) {
            if(s[i]<b.s[i])return true;
            if(s[i]>b.s[i])return false;
        }
        return false;
    }
    bool operator >= (const BigInteger& b) {
        return !(*this<b);
    }
    bool operator == (const BigInteger& b) {
        if(s.size()!=b.s.size())return false;
        for(int i=0; i<s.size(); i++)
            if(s[i]!=b.s[i])return false;
        return true;
    }
    //+
    BigInteger operator + (const BigInteger& b) {
        BigInteger c;
        c.s.clear();
        for(int i=0,g=0; ; i++) {
            if(g==0&&i>=s.size()&&i>=b.s.size())break;
            int x=g;
            if(i<s.size())x+=s[i];
            if(i<b.s.size())x+=b.s[i];
            c.s.push_back(x%BASE);
            g=x/BASE;
        }
        return c;
    }
    //-
    BigInteger operator - (const BigInteger& b) {
        BigInteger c;
        c=*this;
        for(int i=0; i<c.s.size(); i++) {
            int tmp;
            if(i>=b.s.size())tmp=0;
            else tmp=b.s[i];
            if(c.s[i]<tmp) {
                c.s[i+1]-=1;
                c.s[i]+=BASE;
            }
            c.s[i]-=tmp;
        }
        while(c.s.back()==0&&c.s.size()>1)c.s.pop_back();
        return c;
    }
    void operator -= (const BigInteger& b) {
        *this=*this-b;
    }
    //*
    BigInteger operator * (const BigInteger& b) {
        BigInteger c;
        c.s.resize(s.size()+b.s.size());
        for(int i=0; i<s.size(); i++)
            for(int j=0; j<b.s.size(); j++)c.s[i+j]+=s[i]*b.s[j];
        for(int i=0; i<c.s.size()-1; i++) {
            c.s[i+1]+=c.s[i]/BASE;
            c.s[i]%=BASE;
        }
        while(c.s.back()==0&&c.s.size()>1)c.s.pop_back();
        return c;
    }
    friend istream& operator >> (istream& input,BigInteger& x) {
        string s;
        if(!(input>>s))return input;
        x=s;
        return input;
    }
    friend ostream& operator << (ostream& output,const BigInteger& x) {
        output<<x.s.back();
        for(int i=x.s.size()-2; i>=0; i--) {
            char buf[20];
            sprintf(buf,"%08d",x.s[i]);
            for(int j=0; j<strlen(buf); j++)output<<buf[j];
        }
        return output;
    }
};
// /
BigInteger Copy(const BigInteger& b,int x) {
    BigInteger t;
    t.s.resize(b.s.size()+x);
    for(int i=0; i<b.s.size(); i++)t.s[i+x]=b.s[i];
    return t;
}
BigInteger Divide(const BigInteger& a,const BigInteger& b,BigInteger& mod) {
    BigInteger c;
    c.s.resize(a.s.size()-b.s.size()+1);
    mod=a;
    int Pow[(int)log2(BigInteger::BASE)+5];
    Pow[0]=1;
    for(int i=1; i<=log2(BigInteger::BASE); i++)Pow[i]=Pow[i-1]*2;
    for(int i=c.s.size()-1; i>=0; i--) {
        BigInteger t;
        t=Copy(b,i);
        for(int j=log2(BigInteger::BASE); j>=0; j--)
            if(mod>=t*Pow[j]) {
                c.s[i]+=Pow[j];
                mod-=t*Pow[j];
            }
    }
    while(c.s.back()==0&&c.s.size()>1)c.s.pop_back();
    return c;
}
BigInteger a,b;
int main() {
    cin>>a>>b;
    if(a<b)cout<<a+b<<endl<<'-'<<b-a<<endl<<a*b<<endl<<0<<endl<<a<<endl;
    else {
        BigInteger c,d;
        c=Divide(a,b,d);
        cout<<a+b<<endl<<a-b<<endl<<a*b<<endl<<c<<endl<<d<<endl;
    } 
    return 0;
}
```
管理员给过吧，毕竟这是唯一一个真正的题解


---

## 作者：忘无羡机 (赞：40)

发现先前没有什么人发在重载运算符的解法，于是身为心系某谷的**小蒟蒻**我决定挺身而出花了一下午调试出这么一份代码。

------------

虽然速度比不上前面的那些C++和Python大佬，但我这是一条**重载运算符**之后的**高精模板**，而且其中的注释也十分详细作为一个初学者和**第一次发题解**的**小蒟蒻**，希望能对看这篇题解的**神犇**有点帮助

------------

不多说了上代码（**在编译器上服用效果更佳**）：
------------

```
#include<bits/stdc++.h>
using namespace std;

struct data{
    int num[20110];     //此处范围要开到数据范围的两倍,因为乘法时位数会翻倍 
    int len;
    char op;
    data(){ memset(num,0,sizeof(num));  len = 1; op = '+';}
};//注意存之前要倒序处理最高位放最后 
int max(int a,int b){
    return (a > b) ? a : b;
}
bool operator > (data a,data b){//重载了大于判断符,以符号为第一关键字,以长度为第二关键字,以绝对值为第三关键字,注意符号 
    if(a.op == '+' && b.op == '-')  return true;
    if(a.op == '-' && b.op == '+')  return false;
    if(a.len > b.len)               return true;
    if(a.len < b.len)               return false;
    if(a.op == '-' && b.op == '-')
    {
        for(int i = a.len;i >= 1;i --)
            if(a.num[i] > b.num[i])         return false;
            else if(a.num[i] < b.num[i])    return true;
            else if(a.num[i] == b.num[i])   continue;
    }
    if(a.op == '+' && b.op == '+')
    {
        for(int i = a.len;i >= 1;i --)
            if(a.num[i] > b.num[i])         return true;
            else if(a.num[i] < b.num[i])    return false;
            else if(a.num[i] == b.num[i])   continue;
    }
    return false;
}
bool operator < (data a,data b){//重载了小于,原理同上 
    if(a.op == '+' && b.op == '-')  return false;
    if(a.op == '-' && b.op == '+')  return true;
    if(a.len > b.len)               return false;
    if(a.len < b.len)               return true;
    if(a.op == '-' && b.op == '-')
    {
        for(int i = a.len;i >= 1;i --)
            if(a.num[i] > b.num[i])         return true;
            else if(a.num[i] < b.num[i])    return false;
            else if(a.num[i] == b.num[i])   continue;
    }
    if(a.op == '+' && b.op == '+')
    {
        for(int i = a.len;i >= 1;i --)
            if(a.num[i] > b.num[i])         return false;
            else if(a.num[i] < b.num[i])    return true;
            else if(a.num[i] == b.num[i])   continue;
    }
    return false;
}
bool operator ==(data a,data b){//重载了等于,原理同上 
    if(a.len == b.len)
    {
        for(int i = a.len;i >= 1;i --)
        {
            if(a.num[i] != b.num[i])    return false;
            else continue;
        }
        return true;
    }
    return false;
}
data operator + (data a,data b){//求和 
    data c;                             //c为所求的和 
    c.len = max(a.len,b.len);           //此处取最大是为了保证两个加数中的每一位都被算到 
    for(int i = 1;i <= c.len;i ++)      //先预处理得到未进位的答案 
        c.num[i] = a.num[i] + b.num[i]; 
    for(int i = 1;i <= c.len;i ++)      //以下为进位处理,注意从最低位开始扫描 
        if(c.num[i] >= 10)              //如果这位预处理得到的答案大于10则需要进位 
        {
            c.num[i + 1] += c.num[i] / 10;//进位,这就是为什么需要从最低位开始扫,这样可以保证一次性进位干净 
            c.num[i] %= 10;             //保留个位数 
            c.len = max(c.len,i + 1);   //注意:保留下来的长度要确保最高位有进位才需要更改，不然只需要留下两个加数中的最大长度就行 
        }
    return c;
}
data operator - (data a,data b){//求差 
    data c,temp;                        //c为所求的差,temp为交换的过程量 
    c.len = max(a.len,b.len);           //原理和加法一样，保证每一位都算过 
    if(b > a)                           //如果减数比被减数大需要特殊操作 
    {
        c.op = '-';                     //给答案上个负号 
        temp = a,a = b,b = temp;        //交换减数和被减数保证这时的答案大于等于0 
    }
    for(int i = 1;i <= c.len;i ++)      //预处理得到初始答案 
        c.num[i] = a.num[i] - b.num[i];
    for(int i = 1;i <= c.len;i ++)      //一下为借位处理,同样从最低位开始 
        if(c.num[i] < 0)                //如果预处理得到的这一位答案小于0 
        {
            c.num[i] += 10;             //借位 
            c.num[i + 1] -= 1;          //上一位减一 
        }
    return c;
}
data operator * (data a,data b){//求积 
    data c;                             //c为所求的积 
    c.len = a.len + b.len + 1;          //从小开始找一下规律会发现两数相乘会有以下规律
/*
                    a[3]        a[2]        a[1]
*                               b[2]        b[1]
--------------------------------------------------
                a[3]b[1]  a[2]*b[1]   a[1]*b[1] 
+   a[3]b[2]    a[2]b[2]  a[1]*b[2]
--------------------------------------------------
    c[4]          c[3]      c[2]        c[1]

###此时我们注意到一个数的第i位和另一个数的第j位相乘的到的数应该在答案的第i + j - 1位；
###而且不同于加减法的是此时的答案是通过二维枚举得到的需要用累加 
### 
*/ 
    for(int i = 1;i <= a.len;i++)       //每一位依次枚举 
        for(int j = 1;j <= b.len;j++)
            c.num[i + j - 1] += a.num[i]*b.num[j];//累加的意义如上所示 
    for (int i = 1;i <= c.len;i ++)     //和加法一样需要进位，要一次性进位干净 
    {
        if(c.num[i] >= 10)
        {
            c.num[i + 1] += c.num[i] / 10;//进位的值不难理解是当前位除以10以后向下取整 
            c.num[i] %= 10;             //保留各位 
            c.len = max(c.len,i + 1);   //意义和加法一样 
        }
    }
    return c;
}
data numcopy(data a,int l){//转移值的函数 
    data b;
    for (int i=1;i<=a.len;i++) b.num[i+l-1]=a.num[i];
    b.len=a.len+l-1;
    b.op = '+';
    return b;
}
data operator / (data a,data b){//求商 
    data c;
    c.len = a.len - b.len + 1;
    for(int i = c.len;i >= 1;i --)
    {
        data t = numcopy(b,i);          //将除数乘以10的(i - 1)次相当于在枚举商的位数 
        while(a > t || a == t)          //由于懒得写>= 的重载就只好这样不厌其烦了 
        {
            c.num[i]++;                 //商的这一位加一 
            if(a == t) 	 break;			//如果剩下的被除数已经可以被整除了就不用接着操作了        
            a = a - t;					//减去可以保存的值
			while (a.len>0 && !a.num[a.len]) a.len--;         
        }
    }
	while (c.len > 0 && !c.num[c.len]) c.len--;
    return c;
/*
###除法的概念相对比较抽象，需要花点时间去理解 
*/
}
data operator % (data a,data b){//求余,大部分和除法概念一样,最后的返回值只需要返回多次减完剩下的a就行了 
    for(int i = a.len - b.len + 1;i >= 1;i --)
    {
        data t = numcopy(b,i);
        while(a > t || a == t)
        {
            if(a == t)    break;
            a = a - t;
            while (a.len>0&&!a.num[a.len]) a.len--;         
        }
    }
    return a;
}
data kkk(int b){//将一个整数类型转化为data类型，避免了重载很多不同类型间的运算符 
    int t = 0;
    data c;
    while(b)
    { 
        t ++;                           //求位数 
        c.num[t] = b % 10;              //保留这一位的数 
        b /= 10;                        //删去这一位 
    }
    c.len = t;
    return c;
}
data gcd(data x,data y){//递归求最大公约数 
    if(y == kkk(0)) return x;
    else return gcd(y,x % y);
}
//运算符重载 

void get_data(data &a,data &b){//将数据用字符串读入,并处理正负 
    string s1,s2;
    cin >> s1 >> s2;
    if(s1[0] == '-')    a.op = '-',s1.erase(0,1);
    if(s2[0] == '-')    b.op = '-',s2.erase(0,1);
    for(int i = 1;i <= s1.size();i ++)
        a.num[i] = int(s1[s1.size() - i]) - '0';//注意要倒序储存数字 
    a.len = s1.size();
    for(int i = 1;i <= s2.size();i ++)
        b.num[i] = int(s2[s2.size() - i]) - '0';
    b.len = s2.size();
}
void print(data c){
    if(c.op == '-')printf("-");
    bool flag = false;
    for(int i = c.len;i >= 1;i --)
        if(c.num[i] != 0 || flag == true)
        {
            printf("%d",c.num[i]);
            flag = true;
        }
    if(flag == false)
        printf("0");
    printf("\n"); 
}
//初始数据处理 

int main(){
//    freopen("1.in","r",stdin);
    data a,b,c;
    get_data(a,b);
    c = a + b;
    print(c); 
    c = a - b;
    print(c);
    c = a * b;
    print(c);   
    c = a / b;
    print(c);   
    c = a % b;
    print(c); 
}
```


---

## 作者：Great_Influence (赞：35)

python水题

代码：

```python
a=int(input())
b=int(input())
print(a+b)
print(a-b)
print(a*b)
print(a//b)
print(a-a//b*b)
```

---

## 作者：Adove (赞：32)

此篇题解支持负数读入与四则运算，支持修改压位位数，且无论是时间复杂度还是空间复杂度都大大优于其他代码，目前吸氧60ms,2.22MB稳居最优解。

对于除法复杂度的优化，运用了倍增的思想，使用倍增减法代替除法、普通减法，配合压位，大大优化了时空效率。

乘法我试过类似的倍增加法形式，但效率远不如逐位计算。

另外，此份代码的高精乘部分，吸氧812ms水过FFT，最慢的点仅用了276ms

希望能对大家有所帮助

以下是模板↓

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int MAXN=1e5;
const int siz=8;
const long long MOD=1e8;//MOD=10^siz

char ch1[MAXN],ch2[MAXN];
bool f1,f2,f;//0为非负，1为负
long long n;
long long a[MAXN>>2],b[MAXN>>2],s[MAXN>>2];
long long cp[MAXN>>2],lt[MAXN>>2],wsd[MAXN>>2];

void write(long long num[]);//输出高精度数
void clear(long long num[]);//数组重置
void ry(long long num[]);//>>右移一位
void ly(long long num[]);//<<左移一位
void cpy(long long num1[],long long num2[]);//num1=num2
int cmp(long long num1[],long long num2[]);//compare num1 and num2
void pls(long long a[],long long b[]);//plus加法
void mnu(long long a[],long long b[]);//minus减法
void mul(long long a[],long long b[]);//multiply乘法
void div(long long a[],long long b[]);//divided除法

void write(long long num[])
{
	if(f) putchar('-'),f=0;
	printf("%lld",num[num[0]]);
	for(int i=num[0]-1;i;--i) printf("%08lld",num[i]);
	puts("");
}

void clear(long long num[])
{
	for(int i=num[0];i;--i) num[i]=0;
	num[0]=1;
}

void ry(long long num[])
{
	for(int i=num[0];i;--i){
		if((num[i]&1)&&i>1) num[i-1]+=MOD;//将1借到下一位
		num[i]>>=1;
	}if(!num[num[0]]&&num[0]>1) --num[0];
}

void ly(long long num[])
{
	++num[0];
	for(int i=1;i<=num[0];++i){
		num[i]<<=1;
		if(num[i-1]>=MOD) num[i-1]-=MOD,++num[i];//进位，注意后效性
	}if(!num[num[0]]&&num[0]>1) --num[0];
	return;
}

void cpy(long long num1[],long long num2[])
{
	for(int i=num1[0];i>num2[0];--i) num1[i]=0;
	for(int i=0;i<=num2[0];++i) num1[i]=num2[i];
}

int cmp(long long num1[],long long num2[])
{
	if(num1[0]>num2[0]) return 1;
	if(num1[0]<num2[0]) return -1;
	for(int i=num1[0];i;--i){
		if(num1[i]>num2[i]) return 1;
		if(num1[i]<num2[i]) return -1;
	}return 0;
}

void init()
{
	scanf("%s%s",ch1,ch2);
	if(ch1[0]=='-') ch1[0]='0',f1=1;
	if(ch2[0]=='-') ch2[0]='0',f2=1;//符号处理
	int l1=strlen(ch1),l2=strlen(ch2);
	for(int i=l1-1;i>=0;i-=siz){
		long long pw=1;++a[0];
		for(int j=i;j>i-siz&&j>=0;--j){
			a[a[0]]+=(ch1[j]^48)*pw;
			pw=(pw<<3)+(pw<<1);
		}
	}for(int i=l2-1;i>=0;i-=siz){
		long long pw=1;++b[0];
		for(int j=i;j>i-siz&&j>=0;--j){
			b[b[0]]+=(ch2[j]^48)*pw;
			pw=(pw<<3)+(pw<<1);
		}
	}return;//反序读入存储
}

void pls(long long a[],long long b[])
{
	if(f1^f2){
		if(f1) f1^=1,mnu(b,a),f1^=1;//a+b=b-(-a)
		if(f2) f2^=1,mnu(a,b),f2^=1;//a+b=a-(-b)
		return;
	}if(f1&f2){
		f1=f2=0,f^=1,pls(a,b);//两个负数绝对值相加，符号为负
		f1=f2=1;return;
	}clear(s);
	s[0]=max(a[0],b[0])+1;
	for(int i=1;i<=s[0];++i){
		s[i]+=a[i]+b[i];
		if(s[i]>=MOD) s[i]-=MOD,++s[i+1];//进位
	}if(!s[s[0]]&&s[0]>1) --s[0];
	return;
}

void mnu(long long a[],long long b[])
{
	if(f1^f2){
		if(f1) f1^=1,f^=1,pls(a,b);//a-b=-(-a+b)
		if(f2) f2^=1,pls(a,b);//a-b=a+(-b)
		return;
	}if(f1&f2){
		f1=f2=0,mnu(b,a);//a-b=-b-(-a)
		f1=f2=1;return;
	}if(cmp(a,b)==-1) swap(a,b),f^=1;//绝对值相减，符号与绝对值大的数符号相同
	clear(s);
	s[0]=max(a[0],b[0]);
	for(int i=1;i<=s[0];++i){
		s[i]+=a[i]-b[i];
		if(s[i]<0) s[i]+=MOD,--s[i+1];//借位
	}while(!s[s[0]]&&s[0]>1) --s[0];
	return;
}

void mul(long long a[],long long b[])//模拟竖式乘法
{
	if(f1^f2) f^=1;
	clear(s);
	s[0]=a[0]+b[0];
	for(int i=1;i<=a[0];++i){
		for(int j=1;j<=b[0];++j){
			s[i+j-1]+=a[i]*b[j];
			if(s[i+j-1]>=MOD) s[i+j]+=s[i+j-1]/MOD,s[i+j-1]%=MOD;//进位
		}
	}if(!s[s[0]]&&s[0]>1) --s[0];
	return;
}

void div(long long a[],long long b[])
{
	if(f1^f2) f^=1;
	clear(cp),cp[1]=1;clear(lt);
	while(cmp(a,b)!=-1) ly(b),ly(cp);//将除数倍增到不小于被除数，确定商二进制最高位
	while(cp[0]>1||cp[1]){
		if(cmp(a,b)!=-1){
			mnu(a,b),cpy(a,s);//a-=b
			pls(lt,cp),cpy(lt,s);//lt+=cp
		}ry(b),ry(cp);//b>>=1,cp>>=1
	}cpy(s,lt),cpy(lt,a);//s=lt,lt=a，此时，s是商，lt是余数
	return;
}

int main()
{
	init();
	clear(s);
	pls(a,b);
	write(s);
	mnu(a,b);
	write(s);
	mul(a,b);
	write(s);
	div(a,b);
	write(s);
	write(lt);
	return 0;
}
```

---

## 作者：fzj2007 (赞：21)

高精度集合啊

先推我的[blog](https://www.luogu.com.cn/blog/fzj2007/)

然后简单讲解一下压位存储高精度

------------
### (1) 定义
```
static const int MAX=10001;
struct hp{
    int num[MAX];
    
    hp&operator=(const char*);
    hp&operator=(int);
    hp();
    hp(int);
    //以下运算符根据需要定义。。
    bool operator>(const hp&)const;
    bool operator<(const hp&)const;
    bool operator<=(const hp&)const;
    bool operator>=(const hp&)const;
    bool operator!=(const hp&)const;
    bool operator==(const hp&)const;
    hp operator+(const hp&)const;
    hp operator-(const hp&)const;
    hp operator*(const hp&)const;
    hp operator/(const hp&)const;
    hp operator%(const hp&)const;
    
    hp&operator+=(const hp&);
    hp&operator-=(const hp&);
    hp&operator*=(const hp&);
    hp&operator/=(const hp&);
    hp&operator%=(const hp&);
};
```
THEN 
### (2) 赋值和初始化
```
// num[0]用来保存数字位数。利用10000进制可以节省空间和时间。
hp&hp::operator=(const char* c){
    memset(num,0,sizeof(num));
    int n=strlen(c),j=1,k=1;
    for(int i=1;i<=n;i++){
        if(k==10000) j++,k=1;// 10000进制，4个数字才算1位。
        num[j]+=k*(c[n-i]-'0');
        k*=10;
    }
    num[0]=j;
    return *this;
}

hp&hp::operator=(int a){
    char s[MAX];
    sprintf(s,"%d",a);
    return *this=s;
}
hp::hp(){
	memset(num,0,sizeof(num)); 
	num[0]=1;
}
hp::hp(int n){
	*this=n;
}// 目的：支持“hp a=1;”之类的代码。
```
ANE THE THIRD:
### (3) 比较运算符
```
// 如果位数不等，大小是可以明显看出来的。如果位数相等，就需要逐位比较。
bool hp::operator > (const hp &b) const{
    if(num[0]!=b.num[0]) return num[0]>b.num[0];
    for(int i=num[0];i>=1;i--)
        if(num[i]!=b.num[i])
            return (num[i]>b.num[i]);
    return false;
}
//顺手定义了，较好理解，仔细看一下
bool hp::operator<(const hp &b)const{return b>*this;}
bool hp::operator<=(const hp &b)const{return !(*this>b);}
bool hp::operator>=(const hp &b)const{return !(b>*this);}
bool hp::operator!=(const hp &b)const{return (b>*this)||(*this>b);}
bool hp::operator==(const hp &b)const{return !(b>*this)&&!(*this>b);}
```
剩下的：
### (4) 四则运算
### (5) 输入/输出
请参见
### [here](https://www.luogu.com.cn/blog/fzj2007/solution-p1096)
或
### [here](https://www.luogu.com.cn/blog/fzj2007/solution-p1601)
顺便推荐**P1096**和P**1061**


------------
最后贴上~~完美~~（chou lou）的代码
```
#include<bits/stdc++.h>
using namespace std;
const int MAX=10001;
struct hp{
    int num[MAX];
    
    hp&operator=(const char*);
    hp&operator=(int);
    hp();
    hp(int);
    
    bool operator>(const hp&)const;
    bool operator<(const hp&)const;
    bool operator<=(const hp&)const;
    bool operator>=(const hp&)const;
    bool operator!=(const hp&)const;
    bool operator==(const hp&)const;

    hp operator+(const hp&)const;
    hp operator-(const hp&)const;
    hp operator*(const hp&)const;
    hp operator/(const hp&)const;
    hp operator%(const hp&)const;
    
    hp&operator+=(const hp&);
    hp&operator-=(const hp&);
    hp&operator*=(const hp&);
    hp&operator/=(const hp&);
    hp&operator%=(const hp&);
};
// num[0]用来保存数字位数。利用10000进制可以节省空间和时间。
hp&hp::operator=(const char* c){
    memset(num,0,sizeof(num));
    int n=strlen(c),j=1,k=1;
    for(int i=1;i<=n;i++){
        if(k==10000) j++,k=1;// 10000进制，4个数字才算1位。
        num[j]+=k*(c[n-i]-'0');
        k*=10;
    }
    num[0]=j;
    return *this;
}

hp&hp::operator=(int a){
    char s[MAX];
    sprintf(s,"%d",a);
    return *this=s;
}
hp::hp(){
	memset(num,0,sizeof(num)); 
	num[0]=1;
}
hp::hp(int n){
	*this=n;
}// 目的：支持“hp a=1;”之类的代码。

// 如果位数不等，大小是可以明显看出来的。如果位数相等，就需要逐位比较。
bool hp::operator > (const hp &b) const{
    if(num[0]!=b.num[0]) return num[0]>b.num[0];
    for(int i=num[0];i>=1;i--)
        if(num[i]!=b.num[i])
            return (num[i]>b.num[i]);
    return false;
}
bool hp::operator<(const hp &b)const{return b>*this;}
bool hp::operator<=(const hp &b)const{return !(*this>b);}
bool hp::operator>=(const hp &b)const{return !(b>*this);}
bool hp::operator!=(const hp &b)const{return (b>*this)||(*this>b);}
bool hp::operator==(const hp &b)const{return !(b>*this)&&!(*this>b);}
// 注意：最高位的位置和位数要匹配。
//加法 
hp hp::operator+(const hp&b)const{
    hp c;
    c.num[0]=max(num[0],b.num[0]);
    for(int i=1;i<=c.num[0];i++){
        c.num[i]+=num[i]+b.num[i];
        if(c.num[i]>=10000){// 进位
            c.num[i]-=10000;
            c.num[i+1]++;
        }
    }
    if(c.num[c.num[0]+1]>0) c.num[0]++;// 9999+1，计算完成后多了一位
    return c;
}
//减法 
hp hp::operator-(const hp&b)const{
   hp c;
   c.num[0]=num[0];
   for (int i=1;i<=c.num[0];i++){
       c.num[i]+=num[i]-b.num[i];
       if(c.num[i]<0){  // 退位
            c.num[i]+=10000;
            c.num[i+1]--;
        }
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--;// 100000000-99999999
    return c;
}
//顺便声明 
hp&hp::operator+=(const hp &b){return *this=*this+b;}
hp&hp::operator-=(const hp &b){return *this=*this-b;}
//乘法 
hp hp::operator*(const hp&b)const{
    hp c;
    c.num[0]=num[0]+b.num[0]+1;
    for(int i=1;i<=num[0];i++){
        for(int j=1;j<=b.num[0];j++){
            c.num[i+j-1]+=num[i]*b.num[j];            // 和小学竖式的算法一模一样
            c.num[i+j]+=c.num[i+j-1]/10000;            // 进位
            c.num[i+j-1]%=10000;
        }
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--;    // 99999999*0
    return c;
}
//同上 
hp&hp::operator*=(const hp &b){return *this=*this*b;}
hp hp::operator/(const hp&b)const{
    hp c, d;
    c.num[0]=num[0]+b.num[0]+1;
    d.num[0]=0;
    for(int i=num[0];i>=1;i--){
        // 以下三行的含义是：d=d*10000+num[i];
        memmove(d.num+2, d.num+1, sizeof(d.num)-sizeof(int)*2);
        d.num[0]++;
        d.num[1]=num[i];

        // 以下循环的含义是：c.num[i]=d/b; d%=b; 利用二分查找求c.num[i]的上界。
        // 注意，这里是二分优化后除法和朴素除法的区别！
        int left=0,right=9999,mid;
        while(left<right){
            mid = (left+right)/2;
            if(b*hp(mid)<=d) left=mid+1;
            else right=mid;
        }
        c.num[i]=right-1;
        d=d-b*hp(right-1);
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--;    // 99999999/99999999
    return c;            
}
hp hp::operator%(const hp&b)const{
    hp c, d;
    c.num[0]=num[0]+b.num[0]+1;
    d.num[0]=0;
    for(int i=num[0];i>=1;i--){
        // 以下三行的含义是：d=d*10000+num[i];
        memmove(d.num+2, d.num+1, sizeof(d.num)-sizeof(int)*2);
        d.num[0]++;
        d.num[1]=num[i];

        // 以下循环的含义是：c.num[i]=d/b; d%=b; 利用二分查找求c.num[i]的上界。
        // 注意，这里是二分优化后除法和朴素除法的区别！
        int left=0,right=9999,mid;
        while(left<right){
            mid = (left+right)/2;
            if(b*hp(mid)<=d) left=mid+1;
            else right=mid;
        }
        c.num[i]=right-1;
        d=d-b*hp(right-1);
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--;    // 99999999/99999999
    return d;            
}
hp&hp::operator/=(const hp &b){return *this=*this/b;}
hp&hp::operator%=(const hp &b){return *this=*this%b;}
ostream&operator<<(ostream &o,hp &n){
    o<<n.num[n.num[0]];
    for(int i=n.num[0]-1;i>=1;i--){
        o.width(4);
        o.fill('0');
        o<<n.num[i];
    }
    return o;
}
istream & operator>>(istream &in, hp &n){
    char s[MAX];
    in>>s;
    n=s;
    return in;
}
inline int read(){
	int ans=0,flag=1;
	char ch=getchar();
	while((ch>'9'||ch<'0')&&ch!='-') ch=getchar();
	if(ch=='-') flag=-1,ch=getchar();
	while(ch>='0'&&ch<='9'){
		ans=ans*10+ch-'0';
		ch=getchar();
	}
	return ans*flag;
}
hp a,b,c,d,e,f,g; 
int main(){
	cin>>a>>b;
	c=a+b;
	cout<<c<<endl; 
	if(a>=b){
		d=a-b;
		cout<<d<<endl;	
	}else{
		d=b-a;
		cout<<"-"<<d<<endl;	
	}
	e=a*b;
	f=a/b;
	g=a%b;
	cout<<e<<endl<<f<<endl<<g<<endl;
	return 0;
}

  
```
有帮助的，记得点个赞

---

## 作者：DEVILK (赞：17)

BIGNUM大整数型压位（可修改压位数及最大数字长度）

除法用了倍增优化

压到八位的时候应把整型数组开成long long

因为八位的时候进行大整数相乘时会爆掉int

开了long long压八位之后，相比于开int压四位，空间没有优化

但是却可以提高算法的时间效率

还有一种不大常规但是效果很显著的优化：

开了long long后最多可以压位压到9位

比long long压8位和int压4位都要快，消耗的内存少.

各种重载运算符（+、-、*、/、%、>>、<<）

写起来有点繁琐~~（200行好吓人）~~但用起来很简便


------------
虽然有人写过重载运算符了，但是并没有重载/

这个BIGNUM大整数型封装的很完美，既有压位（9位而且可以修改），又有倍增优化的高精度除法

求通过

------------


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

static const int LEN = 10000 + 1;

struct BIGNUM {
	//不定义成全局常量，方便移植BIGNUM类
	static const int BIT = 9;//压位位数
	static const int MOD = 1000000000;//1eBIT 
	
	long long s[LEN];
	bool flag;//负数的话flag为false
	BIGNUM() {
		memset(s, 0, sizeof(s));
		flag = s[0] = 1;
	}
	void init() {
		memset(s, 0, sizeof(s));
		s[0] = 1;
	}
	
    //压位的特殊处理
    //从后向前每BIT个数字放在一组
	BIGNUM operator = (const char *num) {
		int l = strlen(num);
		s[0] = 0;
		for(int i = l - 1; i >= 0; i -= BIT) {
			++s[0];
			long long w = 1;
			for(int j = i; j > i - BIT && j >= 0; j--) {
				s[s[0]] += (num[j] ^ 48) * w;
				w = (w << 1) + (w << 3); 
			}
		}
		return *this;
	}
	BIGNUM operator = (const int num) {
		char a[LEN];
		sprintf(a, "%d", num);
		*this = a;
		return *this;
	}
	BIGNUM(int num) { *this = num; }
	BIGNUM(const char *num) { *this = num; }
	
	BIGNUM operator + (const BIGNUM &a) {
		BIGNUM c;
		int x = 0;
		c.s[0] = max(a.s[0], s[0]) + 1;
		for(int i = 1; i <= c.s[0]; i++) {
			c.s[i] = a.s[i] + s[i] + x;
            //压位其实就是把/10变成了/MOD
            //%10变成了%MOD
			x = c.s[i] / MOD;
			c.s[i] %= MOD;
		}
		while(c.s[c.s[0]] == 0 && c.s[0] > 1) c.s[0]--;
		return c;
	}
	BIGNUM operator += (const BIGNUM &a) {
		*this = *this + a;
		return *this;
	}
	
    //重载逻辑关系运算符
	bool operator == (const BIGNUM &a) {
		int up = max(s[0], a.s[0]);
		for(int i = 0; i < up; i++)
			if(s[up - i] != a.s[up - i]) return false;
		return true;
	}
	bool operator > (const BIGNUM &a) {
		if(s[0] != a.s[0]) return s[0] > a.s[0];
		int up = max(s[0], a.s[0]);
		for(int i = 0; i < up; i++)
			if(s[up - i] != a.s[up - i]) return s[up - i] > a.s[up - i];
		return false;
	}
	bool operator < (const BIGNUM &a) {
		if(s[0] != a.s[0]) return s[0] < a.s[0];
		int up = max(s[0], a.s[0]);
		for(int i = 0; i < up; i++)
			if(s[up - i] != a.s[up - i]) return s[up - i] < a.s[up - i];
		return false;
	}
	bool operator >= (const BIGNUM &a) {
		if(*this > a || *this == a) return true;
		return false;
	}
	bool operator <= (const BIGNUM &a) {
		if(*this < a || *this == a) return true;
		return false;
	}
	
	BIGNUM operator - (const BIGNUM &a) {
		BIGNUM c;
		c.s[0] = max(a.s[0], s[0]) + 1;
		if(*this < a) c.flag = false;
		for(int i = 1; i <= c.s[0]; i++) {
			if(c.flag) c.s[i] += s[i] - a.s[i];
			else c.s[i] += a.s[i] - s[i];
			if(c.s[i] < 0) {
				c.s[i] += MOD;
				c.s[i + 1]--;
			}
		}
        //除去多余的前导零
		while(c.s[c.s[0]] == 0 && c.s[0] > 1) c.s[0]--;
		return c;
	}
	BIGNUM operator -= (const BIGNUM &a) {
		*this = *this - a;
		return *this;
	}
	BIGNUM operator * (const BIGNUM &a) {
		BIGNUM c;
		c.s[0] = s[0] + a.s[0];
		for(int i = 1; i <= s[0]; i++) {
			int x = 0;
			for(int j = 1; j <= a.s[0]; j++) {
				c.s[i + j - 1] += s[i] * a.s[j] + x;
				x = c.s[i + j - 1] / MOD;
				c.s[i + j - 1] %= MOD;
			}
			c.s[i + a.s[0]] = x;
		}
		while(c.s[c.s[0]] > 0) c.s[0]++;
		while(c.s[c.s[0]] == 0 && c.s[0] > 1) c.s[0]--;
		return c;
	}
	BIGNUM operator *= (const BIGNUM &a) {
		*this = *this * a;
		return *this;
	}
	
    //重载左移右移运算符
    //倍增优化减法模拟的除法时需要用
	BIGNUM operator << (const int &num) {
		s[0]++;
		for(int i = 1; i <= s[0]; i++) {
			s[i] <<= num;
			if(s[i - 1] >= MOD)
				s[i - 1] -= MOD, ++s[i];
		}
		while(s[s[0]] == 0 && s[0] > 1) s[0]--;
		return *this;
	}
	BIGNUM operator >> (const int &num) {
		for(int i = s[0]; i >= 1; i--) {
			if((s[i] & 1) && i > 1) s[i - 1] += MOD;
			s[i] >>= num;
		}
		while(s[s[0]] == 0 && s[0] > 1) s[0]--;
		return *this;
	}
	
	BIGNUM operator / (const BIGNUM &k) {
		BIGNUM c = *this, tmp, lt, a;
		a = k;
		tmp.s[1] = 1;
        //找到小于等于c的a
        //使用倍增优化，每次*2
        //复杂度降到了log
        //倍增优化楼下
        //明月の卫——AH 已经说的很详细了，不多说
		while(c >= a) {
			a = a << 1;
			tmp = tmp << 1;
		}
		while(tmp.s[0] > 1 || tmp.s[1]) {
			if(c >= a) {
				c -= a;
				lt += tmp;
			}
			a = a >> 1;
			tmp = tmp >> 1;
		}
		c = lt;//a为当前余数
		while(c.s[c.s[0]] == 0 && c.s[0] > 1) c.s[0]--;
		if(c.s[0] < 1) c.s[c.s[0] = 1] = 0;
		return c;
	}
	BIGNUM operator /= (const BIGNUM &a) {
		*this = *this / a;
		return *this;
	}
    //虽然做除法的时同时求出了商和余数
    //但是返回的只是商的值
    //所以还要重载 mod 运算
	BIGNUM operator % (const BIGNUM &a) {
		BIGNUM d = *this, c = *this / a;
		c *= a;
		return d - c;
	}
	BIGNUM operator %= (const BIGNUM &a) {
		*this = *this % a;
		return *this;
	}
};

//重载读入读出
ostream& operator << (ostream &out, const BIGNUM &a) {
	if(!a.flag) putchar('-');
    //读出时先把第一组BIT位数输出
	//之后的每一组数不足BIT位的要在左边补零
	printf("%d", a.s[a.s[0]]);
	for(int i = a.s[0] - 1; i >= 1; i--)
		printf("%09d", a.s[i]);
	return out;
}
istream& operator >> (istream &in, BIGNUM &a) {
	char str[LEN];
	in >> str;
	a = str;
	return in;
}

BIGNUM a, b;
int main() {
	cin >> a >> b;
	cout << a + b << endl;
	cout << a - b << endl;
	cout << a * b << endl;
	cout << a / b << endl;
	cout << a % b << endl;
}
```
附博客链接：
[内含普通高精度，压位高精度和BIGNUM大整数型](http://www.cnblogs.com/devilk-sjj/p/8992281.html)

---

## 作者：doby (赞：13)

自从有了Python，这迟早要变红题……

但是我们可以正经地练习高精模板的拼凑……

```cpp
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<cstring>
using namespace std;
int a[10009],b[10009],c[20009],tmp[20009],flag,x;
string t,s1,s2;
void print(int a[])//输出
{
    if(a[0]==0){printf("0\n");return;}
    for(int i=a[0];i>0;i--){printf("%d",a[i]);}
    printf("\n");
    return;
}
void clear(int a[])//处理退位情况
{
    while((a[a[0]]==0)&&(a[0]>0)){a[0]--;}
    return;
}
void aplb(string a1,string b1)//a+b
{
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    memset(c,0,sizeof(c));
    a[0]=a1.size();for(int i=0;i<=a[0]-1;i++){a[a[0]-i]=a1[i]-48;}
    b[0]=b1.size();for(int i=0;i<=b[0]-1;i++){b[b[0]-i]=b1[i]-48;}
    c[0]=1,x=0;
    while(c[0]<=a[0]||c[0]<=b[0])
    {
        c[c[0]]=a[c[0]]+b[c[0]]+x,
        x=c[c[0]]/10,
        c[c[0]]=c[c[0]]%10,
        c[0]++;
    }
    c[c[0]]=x;
    clear(c);
    print(c);
}
void amib(string a1,string b1)//a-b
{
    if(a1.size()<b1.size())//判断得数正负
    {
        cout<<"-";
        t=a1,a1=b1,b1=t;//保证能减就要换过来
    }
    if(a1.size()==b1.size())
    {
        for(int i=0;i<a1.size();i++)
        {
            if(a1[i]>b1[i]){break;}
            if(a1[i]<b1[i])
            {
                cout<<"-";
                t=a1,a1=b1,b1=t;
                break;
            }
        }
    }
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    memset(c,0,sizeof(c));
    a[0]=a1.size();for(int i=0;i<=a[0]-1;i++){a[a[0]-i]=a1[i]-48;}
    b[0]=b1.size();for(int i=0;i<=b[0]-1;i++){b[b[0]-i]=b1[i]-48;}
    for(int i=1;i<=a[0]||i<=b[0];i++)
    {
        if(a[i]<b[i])
        {
            a[i]=a[i]+10,
            a[i+1]--;
        }
        c[i]=a[i]-b[i],
        c[0]=i;
    }
    clear(c);
    print(c);
}
void amlb(string a1,string b1)//乘法
{
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    memset(c,0,sizeof(c));
    if(a1=="0"||b1=="0"){printf("0\n");return;}//微小的不存在的特判
    a[0]=a1.size();for(int i=0;i<=a[0]-1;i++){a[a[0]-i]=a1[i]-48;}
    b[0]=b1.size();for(int i=0;i<=b[0]-1;i++){b[b[0]-i]=b1[i]-48;}
    for(int i=1;i<=a[0];i++)
    {
        for(int j=1;j<=b[0];j++)
        {
            c[i+j-1]=c[i+j-1]+a[i]*b[j];
        }
    }
    c[0]=a[0]+b[0];
    for(int i=1;i<=c[0];i++)
    {
        c[i+1]=c[i+1]+c[i]/10,
        c[i]=c[i]%10;
    }
    clear(c);
    print(c);
}
int compare(int a[],int b[])//比大小
{
    if(a[0]>b[0]){return 1;}
    if(a[0]<b[0]){return -1;}
    for(int i=a[0];i>0;i--)
    {
        if(a[i]>b[i]){return 1;}
        if(a[i]<b[i]){return -1;}
    } 
    return 0;
}
void numcpy(int p[],int q[],int det)//神奇的减法
{
    for(int i=1;i<=p[0];i++){q[i+det-1]=p[i];}
    q[0]=p[0]+det-1;
}
void jian(int a[],int b[])//判断够不够减
{ 
    flag=compare(a,b); 
    if(flag==0){a[0]=0;return;}
    if(flag==1) 
    {
        for(int i=1;i<=a[0];i++) 
        {
            if(a[i]<b[i])
            {
```
a[i+1]--,
```cpp
                a[i]=a[i]+10;
            }
            a[i]=a[i]-b[i];
        } 
        clear(a);
        return;
    } 
} 
void chugao(int a[],int b[],int c[])
{
    c[0]=a[0]-b[0]+1;
    for(int i=c[0];i>0;i--)
    {
        memset(tmp,0,sizeof(tmp));
        numcpy(b,tmp,i);
        for(;compare(a,tmp)>=0;)
        {
            c[i]++;
            jian(a,tmp);
        }
    }
    clear(c);
    return;
}
void adib(string a1,string b1)//除法
{
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    memset(c,0,sizeof(c));
    a[0]=a1.size();for(int i=1;i<=a[0];i++){a[i]=a1[a[0]-i]-48;}
    b[0]=b1.size();for(int i=1;i<=b[0];i++){b[i]=b1[b[0]-i]-48;}
    chugao(a,b,c);
    if(a1.size()<b1.size()){printf("0\n");print(a);return;}//a<b也需要特判一下
    if(a1.size()==b1.size())
    {
        for(int i=0;i<a1.size();i++)
        {
            if(a1[i]>b1[i]){break;}
            if(a1[i]<b1[i]){printf("0\n");print(a);return;}
        }
    }
    print(c);
    print(a);
    return;
}
int main()
{
    cin>>s1>>s2;
    aplb(s1,s2);
    amib(s1,s2);
    amlb(s1,s2);
    adib(s1,s2);
}
```

---

## 作者：baqkqpfhv (赞：13)

写个大整数类 使用起来就像int一样方便

该大整数类带符号 使用流输入输出 使用std::vector存储数据 使用std::stringstream解析字符串 复杂度常数略大

对于本题 其实没有必要做一次除法后再做一次模运算（但是没有TLE） 所以可以将 Bigint &div(Bigint &, Bigint, div\_type = division); public掉并在main中直接调用该接口

截至该题解提交时 本题数据要求减法输出绝对值（而题面中并未说明） 所以我在main函数中对于减法加了个判断

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::vector;
using std::string;
using std::stringstream;
using std::setfill;
using std::setw;

class Bigint
{
public :
    //constructor 
    Bigint(long long = 0);
    Bigint(const string &);
    Bigint(const char *str) { *this = string(str); }

    //assignment operators
    Bigint &operator=(long long num) { return *this = Bigint(num); }
    Bigint &operator=(const string &str) { return *this = Bigint(str); }
    Bigint &operator=(const char *str) { return *this = Bigint(str); }

    //relatiional operators 
    bool operator<(const Bigint &obj) const { return cmp(obj) < 0; }
    bool operator>(const Bigint &obj) const { return cmp(obj) > 0; }
    bool operator<=(const Bigint &obj) const { return cmp(obj) <= 0; }
    bool operator>=(const Bigint &obj) const { return cmp(obj) >= 0; }
    bool operator==(const Bigint &obj) const { return cmp(obj) == 0; }
    bool operator!=(const Bigint &obj) const { return cmp(obj) != 0; }

    //arithmetic operators
    Bigint operator+() const { return *this; }
    Bigint operator-() const { return Bigint(-sign_, val_); }
    Bigint operator+(const Bigint &) const;
    Bigint operator-(const Bigint &) const;
    Bigint operator*(const Bigint &) const;
    Bigint operator/(const Bigint &) const;
    Bigint operator%(const Bigint &) const;

    //compound assignment operators
    Bigint &operator+=(const Bigint &obj) { return *this = *this + obj; }
    Bigint &operator-=(const Bigint &obj) { return *this = *this - obj; }
    Bigint &operator*=(const Bigint &obj) { return *this = *this * obj; }
    Bigint &operator/=(const Bigint &obj) { return *this = *this / obj; }
    Bigint &operator%=(const Bigint &obj) { return *this = *this % obj; }

    //increment and decrement operators
    Bigint &operator++() { return *this += 1; }
    Bigint &operator--() { return *this -= 1; }
    Bigint operator++(int);
    Bigint operator--(int);

    //input and output
    friend istream &operator>>(istream &, Bigint &);
    friend ostream &operator<<(ostream &, const Bigint &);

protected :
    enum div_type { division, remainder };
    enum cmp_type { with_sign, without_sign };
    static const int base_ = (int)1e4;
    static const int width_ = 4;
    Bigint(int s, const vector<int> &v) : sign_(s), val_(v) {}
    int cmp(const Bigint &, cmp_type = with_sign) const;
    Bigint &delZero();
    Bigint &add(const Bigint &);
    Bigint &sub(const Bigint &);
    Bigint &mul(const Bigint &, const Bigint &);
    Bigint &div(Bigint &, Bigint, div_type = division);

private :
    int sign_;
    vector<int> val_;
};

int main()
{
    Bigint a, b;
    cin >> a >> b;
    cout << a + b << endl;
    if (a > b) cout << a - b << endl;
    else cout << b - a << endl;
    cout << a * b << endl;
    cout << a / b << endl;
    cout << a % b << endl;
    return 0;
}

Bigint::Bigint(long long num) : sign_(0)
{
    if (num < 0) sign_ = -1, num = -num;
    else if (num > 0) sign_ = 1;
    do
    {
        val_.push_back(num % base_);
        num /= base_;
    } while (num);
}

Bigint::Bigint(const string &str)
{
    sign_ = str[0] == '-' ? -1 : 1;
    int be = str[0] == '-' ? 1 : 0, en = str.size();
    while ((en -= width_) >= be)
    {
        stringstream ss(str.substr(en, width_));
        int temp;
        ss >> temp;
        val_.push_back(temp);
    }
    if ((en += width_) > be)
    {
        stringstream ss(str.substr(be, en - be));
        int temp;
        ss >> temp;
        val_.push_back(temp);
    }
    delZero();
}

Bigint Bigint::operator+(const Bigint &obj) const
{
    if (sign_ * obj.sign_ == 1)
    {
        Bigint temp;
        return cmp(obj, without_sign) >= 0 ? (temp = *this).add(obj) : (temp = obj).add(*this);
    }
    else if (sign_ * obj.sign_ == -1) return *this - -obj;
    else return sign_ == 0 ? obj : *this;
}

Bigint Bigint::operator-(const Bigint &obj) const
{
    if (sign_ * obj.sign_ == 1)
    {
        Bigint temp;
        return cmp(obj, without_sign) >= 0 ? (temp = *this).sub(obj) : (temp = -obj).sub(*this);
    }
    else if (sign_ * obj.sign_ == -1) return *this + -obj;
    else return sign_ == 0 ? -obj : *this;
}

inline Bigint Bigint::operator*(const Bigint &obj) const
{
    Bigint temp;
    return (temp.sign_ = sign_ * obj.sign_) == 0 ? temp : temp.mul(*this, obj);
}

inline Bigint Bigint::operator/(const Bigint &obj) const
{
    Bigint temp, mod = *this;
    return cmp(obj, without_sign) < 0 || (temp.sign_ = sign_ * obj.sign_) == 0 ? temp : temp.div(mod, obj);
}

inline Bigint Bigint::operator%(const Bigint &obj) const
{
    Bigint temp, mod = *this;
    return cmp(obj, without_sign) < 0 || (temp.sign_ = sign_) == 0 ? mod : temp.div(mod, obj, remainder);
}

inline Bigint Bigint::operator++(int)
{
    Bigint temp = *this;
    ++*this;
    return temp;
}

inline Bigint Bigint::operator--(int)
{
    Bigint temp = *this;
    --*this;
    return temp;
}

inline istream &operator>>(istream &in, Bigint &obj)
{
    string str;
    if (in >> str) obj = str;
    return in;
}

ostream &operator<<(ostream &out, const Bigint &obj)
{
    if (obj.sign_ == -1) cout << '-';
    out << obj.val_.back();
    for (int i = obj.val_.size() - 2; i >= 0; i--)
        out << setw(Bigint::width_) << setfill('0') << obj.val_[i];
    return out;
}

int Bigint::cmp(const Bigint &obj, cmp_type typ) const
{
    if (typ == with_sign && sign_ != obj.sign_) return sign_ - obj.sign_;
    int sign = typ == with_sign ? sign_ : 1;
    if (val_.size() != obj.val_.size()) return sign * (val_.size() - obj.val_.size());
    for (int i = val_.size() - 1; i >= 0; i--)
        if (val_[i] != obj.val_[i]) return sign * (val_[i] - obj.val_[i]);
    return 0;
}

inline Bigint &Bigint::delZero()
{
    while(val_.back() == 0 && val_.size() > 1) val_.pop_back();
    if (val_.back() == 0) sign_ = 0;
    return *this;
}

Bigint &Bigint::add(const Bigint &obj)
{
    int ts = val_.size(), os = obj.val_.size();
    for (int i = 0; i < os; i++) val_[i] += obj.val_[i];
    val_.push_back(0);
    for (int i = 0; i < ts; i++)
        if (val_[i] >= base_) val_[i] -= base_, ++val_[i + 1];
    return delZero();
}

Bigint &Bigint::sub(const Bigint &obj)
{
    int pos = obj.val_.size();
    for (int i = 0; i < pos; i++)
        if ((val_[i] -= obj.val_[i]) < 0) val_[i] += base_, --val_[i + 1];
    while (val_[pos] < 0) val_[pos] += base_, --val_[++pos];
    return delZero();
}

Bigint &Bigint::mul(const Bigint &a, const Bigint &b)
{
    int as = a.val_.size(), bs = b.val_.size();
    val_.resize(as + bs);
    for (int i = 0; i < as; i++) for (int j = 0; j < bs; j++)
    {
        int x = i + j;
        val_[x] += a.val_[i] * b.val_[j];
        val_[x + 1] += val_[x] / base_;
        val_[x] %= base_;
    }
    return delZero();   
}

Bigint &Bigint::div(Bigint &a, Bigint b, div_type typ)
{
    int move = a.val_.size() - b.val_.size();
    val_.resize(move + 1);
    b.val_.insert(b.val_.begin(), move, 0);
    for (int i = move; i >= 0; i--)
    {
        int left = 0, right = base_;
        while (left + 1 < right)
        {
            int mid = (left + right) >> 1;
            if (a.cmp(b * Bigint(mid), without_sign) >= 0) left = mid;
            else right = mid;
        }
        val_[i] = left;
        a.sub(b * Bigint(left));
        b.val_.erase(b.val_.begin());
    }
    return typ == division ? delZero() : a;
}
```

---

