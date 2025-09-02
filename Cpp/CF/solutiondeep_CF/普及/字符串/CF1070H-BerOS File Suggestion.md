# 题目信息

# BerOS File Suggestion

## 题目描述

Polycarp is working on a new operating system called BerOS. He asks you to help with implementation of a file suggestion feature.

There are $ n $ files on hard drive and their names are $ f_1, f_2, \dots, f_n $ . Any file name contains between $ 1 $ and $ 8 $ characters, inclusive. All file names are unique.

The file suggestion feature handles queries, each represented by a string $ s $ . For each query $ s $ it should count number of files containing $ s $ as a substring (i.e. some continuous segment of characters in a file name equals $ s $ ) and suggest any such file name.

For example, if file names are "read.me", "hosts", "ops", and "beros.18", and the query is "os", the number of matched files is $ 2 $ (two file names contain "os" as a substring) and suggested file name can be either "hosts" or "beros.18".

## 样例 #1

### 输入

```
4
test
contests
test.
.test
6
ts
.
st.
.test
contes.
st
```

### 输出

```
1 contests
2 .test
1 test.
1 .test
0 -
4 test.
```

# AI分析结果

### 题目中文重写
# BerOS文件建议

## 题目描述
Polycarp正在开发一个名为BerOS的新操作系统。他请你帮忙实现一个文件建议功能。

硬盘上有 $n$ 个文件，它们的文件名分别为 $f_1, f_2, \dots, f_n$。每个文件名包含 $1$ 到 $8$ 个字符（包含 $1$ 和 $8$）。所有文件名都是唯一的。

文件建议功能处理查询，每个查询由一个字符串 $s$ 表示。对于每个查询 $s$，它应该计算包含 $s$ 作为子串（即文件名中的某个连续字符段等于 $s$）的文件数量，并建议一个这样的文件名。

例如，如果文件名是 "read.me"、"hosts"、"ops" 和 "beros.18"，查询为 "os"，则匹配的文件数量为 $2$（有两个文件名包含 "os" 作为子串），建议的文件名可以是 "hosts" 或 "beros.18"。

## 样例 #1

### 输入
```
4
test
contests
test.
.test
6
ts
.
st.
.test
contes.
st
```

### 输出
```
1 contests
2.test
1 test.
1.test
0 -
4 test.
```

### 题解综合分析与结论
|作者|思路|算法要点|解决难点|评分|
| ---- | ---- | ---- | ---- | ---- |
|mrsrz|对所有给定串首尾相连建后缀数组，询问串在后缀数组上二分匹配，二分+ST表得出区间后转化为区间数颜色问题，用离线莫队解决|后缀数组、二分查找、ST表、离线莫队|后缀数组构建、区间数颜色问题处理|3星|
|huyangmu|先遍历 $n$ 个字符串，枚举起点并向后遍历，统计每个子串出现在哪个字符串中及出现次数，同时标记避免重复计数|枚举子串、map记录|避免同一字符串中相同子串重复计数|4星|
|Super_Builder|把字符串的每一个子串放到 `map` 里，用另一个 `map` 判断子串是否在当前字符串出现过，避免重复计数，再用一个 `map` 记录每个子串对应哪个字符串|枚举子串、map记录|避免同一字符串中相同子串重复计数|4星|
|Tx_Lcy|用 `map` 记录每个子串分别包含于哪几个串，枚举子串时用另一个 `map` 避免重复记录|枚举子串、map记录|避免同一字符串中相同子串重复记录|4星|
|nekko|将 $n$ 个字符串的所有后缀去重后插入到 $trie$ 树中，匹配时访问最后节点获取匹配字符串|trie树、后缀插入|后缀去重插入trie树|3星|
|Dilute|用字符串hash思想，$O(len^2)$ 枚举子串加入 `map`，统计子串出现次数和最后出现位置|枚举子串、map记录|避免同一字符串中相同子串重复计数|3星|

### 所选题解
- **huyangmu（4星）**
    - 关键亮点：思路清晰，通过枚举子串并用 `map` 记录，同时使用标记避免重复计数，代码简洁易懂。
    - 核心代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, q;
string s;
map<string, string> mp;
map<string, int> pos;
map<string, bool> vis;
signed main (){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i){
        cin >> s;
        vis.clear();
        for (int j = 0; j < s.size(); ++j){
            string sa = "";
            for (int k = j ; k < s.size(); ++k){
                sa += s[k];
                if (vis[sa]) continue;
                mp[sa] = s;
                ++pos[sa];
                vis[sa] = 1;
            }
        }
    }
    cin >> q;
    while (q --){
        cin >> s;
        if (!mp.count(s)) cout << "0 -" << '\n';
        else cout << pos[s] << ' ' << mp[s] << '\n';
    } 
    return 0;
}
```
    - 核心实现思想：先输入 $n$ 个字符串，对于每个字符串，枚举其所有子串，使用 `vis` 标记避免同一字符串中相同子串重复计数，用 `mp` 记录子串对应的文件名，`pos` 记录子串出现次数。最后处理 $q$ 个查询，根据 `mp` 判断是否存在该子串并输出结果。

- **Super_Builder（4星）**
    - 关键亮点：同样利用 `map` 记录子串信息，思路简洁，代码结构清晰。
    - 核心代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long
map<string,int>mp;
map<string,string>mp2;
map<string,bool>mp3;
int n,m;
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        mp3.clear();
        for(int i=0;i<s.size();i++){
            string tmp="";
            for(int j=i;j<s.size();j++){
                tmp+=s[j];
                if(!mp3[tmp]){
                    mp3[tmp]=1;
                    mp[tmp]++;
                    mp2[tmp]=s;
                }
            }
        }
    }
    cin>>m;
    for(int i=1;i<=m;i++){
        string s;
        cin>>s;
        if(!mp[s]){
            cout<<"0 -\n";
        }
        else{
            cout<<mp[s]<<" "<<mp2[s]<<'\n';
        }
    }
    return 0;
}
```
    - 核心实现思想：输入 $n$ 个字符串，对于每个字符串枚举子串，用 `mp3` 标记避免重复计数，`mp` 记录子串出现次数，`mp2` 记录子串对应的文件名。处理 $m$ 个查询，根据 `mp` 判断是否存在该子串并输出结果。

- **Tx_Lcy（4星）**
    - 关键亮点：使用 `map< string,vector<string> >` 记录每个子串包含于哪些字符串，思路独特，便于查询。
    - 核心代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rint register int
map< string,vector<string> >mp;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n;cin>>n;
    for (rint i=1;i<=n;++i){
        string s;cin>>s;
        int len=s.length();
        map<string,int>mpp;
        for (rint j=0;j<len;++j)
            for (rint k=j;k<len;++k){
                string s1=s.substr(j,k-j+1);
                if (mpp[s1]==0) mpp[s1]=1,mp[s1].push_back(s);
            }
    }
    int q;cin>>q;
    while (q--){
        string t;cin>>t;
        if (mp[t].size()==0) cout<<"0 -\n";
        else cout<<(int)(mp[t].size())<<' '<<mp[t][0]<<'\n';
    }
    return 0;
}
```
    - 核心实现思想：输入 $n$ 个字符串，对于每个字符串枚举子串，用 `mpp` 标记避免重复记录，`mp` 记录每个子串包含于哪些字符串。处理 $q$ 个查询，根据 `mp` 判断是否存在该子串并输出结果。

### 最优关键思路或技巧
由于每个文件名长度最大为 $8$，可以枚举所有文件名的子串，使用 `map` 记录子串出现次数和对应的文件名，避免同一字符串中相同子串重复计数，从而在查询时 $O(1)$ 时间得到结果。

### 可拓展之处
同类型题：字符串匹配相关问题，如给定多个字符串，查询某个字符串是多少个字符串的子串。类似算法套路：可以使用 `map` 记录子串信息，也可以使用 $trie$ 树、后缀数组等数据结构处理字符串匹配问题。

### 洛谷推荐题目
- P3370 【模板】字符串哈希
- P2580 于是他错误的点名开始了（trie树应用）
- P5496 【模板】回文自动机（PAM）

### 个人心得摘录与总结
huyangmu：原代码未考虑一个字符串中相同子串重复计数问题，提交后发现错误，通过添加 `map<string, bool> vis` 标记解决。总结：在处理字符串子串统计问题时，要注意避免同一字符串中相同子串重复计数。 

---
处理用时：63.49秒