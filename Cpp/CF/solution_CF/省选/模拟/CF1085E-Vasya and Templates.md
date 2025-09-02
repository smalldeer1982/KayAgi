# Vasya and Templates

## 题目描述

Vasya 拥有三个字符串 $s$、$a$ 和 $b$，它们都只包含前 $k$ 个拉丁字母。

我们定义“模板”为长度为 $k$ 的字符串，且每个前 $k$ 个拉丁字母在其中恰好出现一次（因此共有 $k!$ 种不同的模板）。将模板 $p$ 应用于字符串 $s$，即将 $s$ 中的每个字符 $c$ 替换为 $p_i$，其中 $i$ 是字母 $c$ 在字母表中的序号。例如，将模板 "bdca" 应用于字符串 "aabccd"，得到字符串 "bbdcca"。

Vasya 想知道，是否存在这样一个模板，使得将其应用于 $s$ 后得到的字符串，字典序不小于字符串 $a$，且不大于字符串 $b$。

如果存在多个满足条件的模板，输出任意一个即可。

若对于某个 $i$（$1 \le i \le n$），有 $a_i < b_i$，且对于所有 $j$（$1 \le j < i$），有 $a_j = b_j$，则称字符串 $a$ 的字典序小于字符串 $b$。

你需要独立地回答 $t$ 组测试数据。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
4
bbcb
aada
aada
3
abc
bbb
bbb
```

### 输出

```
YES
badc
NO
```

# 题解

## 作者：Hoks (赞：1)

## 前言
大分讨题，原本看了一眼感觉不能评 $2300$ 的但是被恶心到了。

摘自[杂题选做](https://www.luogu.com.cn/training/499842)。
## 思路分析
比较显然的思路，直接考虑 dfs 尝试。

其实这个 dfs 长的就挺像数位 dp 的了，我们存下来那些字母被映射过了，还有字母映射成了什么，尝试搜索。

显然影响的条件还有一个就是是否贴着上下界。

因为这题有上界也有下界，所以要开两个标记变量。

搜索暴力尝试下，如果当前字符已经有过映射了，直接拿有的映射尝试。

否则枚举下界到上界的所有字符尝试填进去，如果不可行就撤回。

最后对于没有映射的字符，直接枚举尝试映射即可。

具体细节还是要看代码了。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,M=150,INF=0x3f3f3f3f3f3f3f3f;
int n,k,v[M],mp[M];char s[N],a[N],b[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline bool dfs(int u,bool f1,bool f2)
{
    if(u==n+1||!(f1||f2)) return 1;
    int up=f1?a[u]:0,dn=f2?b[u]:k+1,x=v[s[u]];
    if(x)
    {
        if(x<up||x>dn) return 0;
        return dfs(u+1,f1&&x==up,f2&&x==dn);
    }
    for(int j=up;j<=dn;j++)
    {
        if(mp[j]) continue;mp[v[s[u]]=j]=s[u];
        if(dfs(u+1,f1&&j==up,f2&&j==dn)) return 1;
        v[s[u]]=mp[v[s[u]]]=0;
    }
    return 0;
}
signed main()
{
    int T=read();
    while(T--)
    {
        k=read();rd(s,n=0),rd(a,n=0),n=0;rd(b,n);
        for(int i=1;i<=k+2;i++) mp[i]=v[i]=0;mp[0]=mp[k+1]=-1;
        for(int i=1;i<=n;i++) a[i]-=96,b[i]-=96,s[i]-=96;
        if(!dfs(1,1,1)){put("NO\n");continue;}
        for(int i=1,j=1;i<=k;i++){while(mp[j]) j++;if(!v[i]) mp[v[i]=j]=i;}
        put("YES\n");for(int i=1;i<=k;i++) put(v[i]+96);put('\n');
    }
    genshin:;flush();return 0;
}
```

---

## 作者：Qiaoqia (赞：0)

大分讨。

如果 $a$ 串和 $b$ 串当前位之间有可用的字符，那么就填上这个字符，后面就可以随便填了。  
如果 $a$ 和 $b$ 当前位是一样的，那么显然只能填这个字符。  
否则就把 $a$ 和 $b$ 当前位置都试一下，具体来说，是枚举当前位置和 $a/b$ 相同，后面一位填最大/最小。

那么就来考虑怎么实现这个东西。

1. 如果当前位置上下界之间有空的。
	1. 如果 $s$ 这一位没有被映射过。
    	1. 如果上下界之间有一个字母可用，填上这个字母，后面随便填。
        2. 尝试压着下界行不行。
        3. 尝试压着上界行不行。
        3. 如果都不行返回 NO。
    2. 如果被映射过了。
    	1. 映射成的字母在上下界中间则随便构造。
        2. 否则尝试上下界行不行。
2. 如果上下界是一样的。
	1. 如果被映射过了。  
   		和当前一样就继续，否则返回 NO。
    2. 没被映射过则填上并继续。
3. 如果上下界不一样。
	1. 尝试上下界行不行。

然后考虑怎么“尝试”。

1. 如果压着上界。
	2. 当前位没有映射过。
    	1. 填上最小的，如果小于上界则后面随便构造，大于上界返回 NO，否则填了之后继续往下处理。
    3. 当前位置被映射过。
    	1. 小于上界随便构造，大于上界返回 NO，否则继续往下。
2. 下界也是类似的。

然后就写成了这样 130+ 行的代码。  

一看 cf 最短解发现只有 40 行，我也不知道他怎么做到的 /dk。


```cpp
#include <bits/stdc++.h>
// #define DEBUG
namespace Qiaoqia { 
std::string s, a, b;
int k;
std::string con(int p, std::vector<int> map, std::vector<int> rec, int fg1, int fg2) {
    std::vector<int> rem;
    for (int i = 0; i < k; i++)
        if (rec[i] == -1) rem.push_back(i);
    if ((fg1 && fg2) || p == (int)s.size()) {
        std::string res = "YES\n";
        for (int i = 0; i < k; i++)
            if (map[i] == -1) {
                map[i] = rem.back();
                rec[rem.back()] = i; 
                rem.pop_back();
            }
        for (int i = 0; i < k; i++) res += char(map[i] + 'a');
        #ifdef DEBUG
        std::string _res;
        for (auto c : s) _res += char(map[c - 'a'] + 'a');
        if (_res >= a && _res <= b) std::cout << "AC";
        else std::cout << "WA(" << _res << ")";
        return "";
        #endif
        return res;
    }
    else if (fg1) {
        if (map[s[p] - 'a'] == -1) {
            if (rem.size() && rem[0] < b[p] - 'a') {
                auto tmap = map, trec = rec;
                tmap[s[p] - 'a'] = rem[0], trec[rem[0]] = s[p] - 'a';
                return con(p + 1, tmap, trec, 1, 1);
            }
            else if (rem.size() && rem[0] == b[p] - 'a') {
                auto tmap = map, trec = rec;
                tmap[s[p] - 'a'] = rem[0], trec[rem[0]] = s[p] - 'a';
                return con(p + 1, tmap, trec, 1, 0);
            }
            else return "NO";
        }
        else {
            if (map[s[p] - 'a'] < b[p] - 'a')
                return con(p + 1, map, rec, 1, 1);
            else if (map[s[p] - 'a'] == b[p] - 'a') 
                return con(p + 1, map, rec, 1, 0);
            else return "NO";
        }
    }
    else {
        if (map[s[p] - 'a'] == -1) {
            if (rem.size() && rem.back() > a[p] - 'a') {
                auto tmap = map, trec = rec;
                tmap[s[p] - 'a'] = rem.back(), trec[rem.back()] = s[p] - 'a';
                return con(p + 1, tmap, trec, 1, 1);
            }
            else if (rem.size() && rem.back() == a[p] - 'a') {
                auto tmap = map, trec = rec;
                tmap[s[p] - 'a'] = rem.back(), trec[rem.back()] = s[p] - 'a';
                return con(p + 1, tmap, trec, 0, 1);
            }
            else return "NO";
        }
        else {
            if (map[s[p] - 'a'] > a[p] - 'a')
                return con(p + 1, map, rec, 1, 1);
            else if (map[s[p] - 'a'] == a[p] - 'a') 
                return con(p + 1, map, rec, 0, 1);
            else return "NO";
        }
    }
}
void solve() {
    std::cin >> k >> s >> a >> b;
    if (a > b) return std::cout << "NO\n", void();
    std::vector<int> map(26, -1), rec(26, -1);
    for (int i = 0; i < (int)a.size(); i++) {
        bool flag = 0;
        if (a[i] < b[i] - 1 && map[s[i] - 'a'] == -1) {
            for (int j = a[i] + 1 - 'a'; j < b[i] - 'a'; j++)
                if (rec[j] == -1) {
                    auto tmap = map, trec = rec;
                    tmap[s[i] - 'a'] = j, trec[j] = s[i] - 'a';
                    std::cout << con(i + 1, tmap, trec, 1, 1) << '\n';
                    return;
                }
            flag = 1;
        }
        else if (a[i] < b[i] - 1 &&
                 map[s[i] - 'a'] > a[i] - 'a' && 
                 map[s[i] - 'a'] < b[i] - 'a') 
            return std::cout << con(i + 1, map, rec, 1, 1) << '\n', void();
        else if (a[i] != b[i]) flag = 1;
        else {
            if (map[s[i] - 'a'] == -1 && rec[a[i] - 'a'] == -1) 
                map[s[i] - 'a'] = a[i] - 'a', rec[a[i] - 'a'] = s[i] - 'a';
            else if (map[s[i] - 'a'] != a[i] - 'a' ||
                     rec[a[i] - 'a'] != s[i] - 'a') 
                return std::cout << "NO\n", void();
        }
        if (flag) {
            auto tmap = map, trec = rec;
            if (tmap[s[i] - 'a'] == -1 && trec[a[i] - 'a'] == -1) {
                tmap[s[i] - 'a'] = a[i] - 'a', trec[a[i] - 'a'] = s[i] - 'a';
                auto ans = con(i + 1, tmap, trec, 0, 1);
                if (ans == "NO" && trec[b[i] - 'a'] == -1) {
                    tmap = map, trec = rec;
                    tmap[s[i] - 'a'] = b[i] - 'a', trec[b[i] - 'a'] = s[i] - 'a';
                    std::cout << con(i + 1, tmap, trec, 1, 0) << '\n';
                    return;
                }
                else return std::cout << ans << '\n', void();
            }
            else if (tmap[s[i] - 'a'] == -1 && trec[b[i] - 'a'] == -1) {
                tmap[s[i] - 'a'] = b[i] - 'a', trec[b[i] - 'a'] = s[i] - 'a';
                std::cout << con(i + 1, tmap, trec, 1, 0) << '\n';
                return;
            }
            else if (tmap[s[i] - 'a'] == a[i] - 'a')
                return std::cout << con(i + 1, tmap, trec, 0, 1) << '\n', void();
            else if (tmap[s[i] - 'a'] == b[i] - 'a')
                return std::cout << con(i + 1, tmap, trec, 1, 0) << '\n', void();
            else return std::cout << "NO\n", void();
        }
    }
    std::cout << con(s.size(), map, rec, 1, 1) << '\n';    
}
void main() {
	int T;
	std::cin >> T;
	while (T--) solve();
}
}
void _() { std::ios::sync_with_stdio(false), std::cin.tie(nullptr); }
int main() { _(); Qiaoqia::main(); }
```

---

