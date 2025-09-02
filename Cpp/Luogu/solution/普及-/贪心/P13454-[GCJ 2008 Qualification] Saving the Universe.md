# [GCJ 2008 Qualification] Saving the Universe

## 题目描述

有一个都市传说：如果你在 Google 首页搜索“Google”，宇宙就会崩溃。我们有个秘密要告诉你……这是真的！请不要尝试，也不要告诉别人。好吧，其实不是，我们只是开玩笑。

但在遥远的另一个宇宙中，情况却并非如此。在那个宇宙里，如果你在任何搜索引擎上搜索该搜索引擎的名字，宇宙真的会崩溃！

为了解决这个问题，人们想出了一个有趣的办法。所有的查询会被集中到一起，然后交给一个中央系统来决定每个查询由哪个搜索引擎处理。中央系统会将一系列查询发送给某个搜索引擎，并且可以随时切换到另一个搜索引擎。所有查询必须按照收到的顺序处理。中央系统绝不能将一个查询发送给名字与该查询相同的搜索引擎。为了降低成本，切换搜索引擎的次数应尽量少。

你的任务是：假设我们以最优方式编程，请你告诉我们中央系统需要切换多少次搜索引擎。

## 说明/提示

**样例解释**

在第一个测试用例中，一种可行的方案是先使用 Dont Ask，在第 8 个查询后切换到 NSM。

在第二个测试用例中，你可以一直使用 B9，无需切换。

**数据范围**

- $0 < N \leq 20$

**小数据集（5 分，测试点 1 - 可见）**

- $2 \leq S \leq 10$
- $0 \leq Q \leq 100$

**大数据集（20 分，测试点 2 - 隐藏）**

- $2 \leq S \leq 100$
- $0 \leq Q \leq 1000$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
5
Yeehaw
NSM
Dont Ask
B9
Googol
10
Yeehaw
Yeehaw
Googol
B9
Googol
NSM
B9
NSM
Dont Ask
Googol
5
Yeehaw
NSM
Dont Ask
B9
Googol
7
Googol
Dont Ask
NSM
NSM
Yeehaw
Yeehaw
Googol```

### 输出

```
Case #1: 1
Case #2: 0```

# 题解

## 作者：long_long_inf (赞：1)

# 思路

这题想起来还是比较简单的，但有些细节要注意。

大体思路就是贪心了。我们看最开始用哪个浏览器可以查询最久，就用哪个。对于剩下的查询内容，重复以上步骤直至结束。

我们可以用 map 来存储各个浏览器是否还能查询。最开始，将它们的值都对应为 $1$，等到它们无法进行查询的时候将值改为 $0$。如果所有值都为零，就证明所有浏览器到此时都不能连续查询了，所以此时必须换浏览器。

# 代码
```cpp
#include <iostream>
#include <string>
#include <map>
using namespace std;
string s[105];
map <string, bool> mp;
int main() {
    int t;
    cin >> t;
    for (int k = 1; k <= t; k++) {
        int n; //为与数组区分以及习惯，不使用原变量名
        cin >> n;
        getline(cin, s[0]); //输入换行字符
        for (int i = 1; i <= n; i++) {
            getline(cin, s[i]); //这个函数用于整行输入，本题因有空格而必须调用
            mp[s[i]] = 1;
        }
        int q;
        cin >> q;
        getline(cin, s[0]);
        int ans = 0; //统计答案
        int cnt = 0; //统计有多少浏览器此时已不能连续使用
        for (int i = 1; i <= q; i++) {
            string s1;
            getline(cin, s1);
            if (mp[s1] == 1) cnt++;
            mp[s1] = 0;
            if (cnt == n) {
                ans++;
                cnt = 1; //理由同下
                for (int j = 1; j <= n; j++) mp[s[j]] = 1; //将其重置
                mp[s1] = 0; //因为这个浏览器只能查询到上一个，到这儿就不能查询了
            }
        }
        cout << "Case #" << k << ": " << ans << endl;
    }
    return 0;
}

---

## 作者：pengyirui (赞：0)

这是一道很好的贪心题。
## 贪心策略
使用 set 存储，每输入一个字符串就删除 set 中对应的字符串，如果空了答案就 $+1$，并且把 set 重置为所有搜索引擎的集合，**并且在新集合中删除次搜索引擎**。    
时间复杂度：$O(NQ\log Q)$，$\log$ 是因为 set 的插入复杂度。
### 一个小小的优化
#### 优化思路
set 自带有插入和删除的时间复杂度 $\log n$，考虑优化掉这个 $\log$。
:::info[unordered_set 介绍] 
#### 介绍
在 c++ 中，有一个数据结构，叫做 unordered_set，它是 C++ 标准模板库（STL）提供的一种容器，用于存储唯一元素且不保持元素顺序。
#### 头文件
```cpp lines=2-2
#include<bits/stdc++.h>//万能头文件
#include<unordered_set>//真的头文件
```
#### 底层实现
unordered_set 的底层实现基于哈希表。    
##### 哈希方式
默认使用 std::hash<T>，但可以**自定义哈希函数**。大家可以到[这里](https://blog.csdn.net/King_lxh/article/details/146368921)和[这里](https://blog.csdn.net/li1615882553/article/details/87875235)详细了解，再次不多赘述。~~（我绝对不会告诉你我不会。）~~
#### 时间复杂度
平均时间复杂度为 $O(1)$，但是最坏可以卡到 $O(n)$。     
#### 使用方法
与 set 几乎一样，支持 != 操作。
:::
所以本题可以使用 unordered_set 优化，**平均**时间复杂度 $O(NQ)$，截止本题解交审，最优解用时第二。（空间不管。）
## 贪心证明
分讨，注意题目中不能改变搜索顺序。
1. 如果当前集合非空，那么还在集合中的搜索引擎肯定没有在**当前轮**（指上次清空后到现在）需要搜索，在上一轮结束后，直接切换到它即可。
2. 如果当前集合已经空了，那么当前轮一定不可能存在搜索引擎可以在不切换的情况下搜索完，故选择使用当前引擎直到前一个搜索引擎，然后必须切换引擎。（不然宇宙真的会崩溃，你真的会 WA。）     
于是，可以得出贪心策略正确。
## 代码
```cpp lines=17-17 
#include<bits/stdc++.h>
using namespace std;
int n,m;
unordered_set<string> us,us2;
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
	int T;
    cin>>T;
    for(int i=1;i<=T;++i)
    {
        us.clear();
        us2.clear();
        cin>>n;
        cin.ignore();
        while(n--)
        {
            string s;
            getline(cin,s);
            us.insert(s);
        }
        cin>>m;
        cin.ignore();
        us2=us;
        int ans=0;
        while(m--)
        {
            string s;
            getline(cin,s);
            us2.erase(s);
            if(us2.empty())
            {
                ans++;
                us2=us;
                us2.erase(s);
            }
        }
        cout<<"Case #"<<i<<": "<<ans<<"\n";
    }
	return 0;
}
```
:::warning[警告]
- 注意代码中的高亮部分，以及第 25 行的相同代码，这句代码是为了去除多余的换行，不然你会 TLE。（[记录](https://www.luogu.com.cn/record/228749436)）。    
- 还有，对于本题，请**务必**使用 getline，因为搜索引擎有空格！（出题人太坏了。）（[记录*2](https://www.luogu.com.cn/record/228750095)）。~~别告我卡评测呀。~~
:::
我的讲解到此结束，感谢您的阅读。

---

## 作者：DevilsFlame (赞：0)

~~被橙题坑得最惨的一次。~~

贪心思路：连续取一段区间，直到出现 $S$ 种引擎为之，即选出若干个区间，使区间内字符串种类数为 $S - 1$。

证明：  
设区间 $[l,r]$，其中 $[l,k],[k + 1,R](k < r)$ 满足以上贪心条件。假设先选 $[l,k_2],(k_2 < k)$ 为最优，应该发现了吧，区间 $[k_2 + 1,r]$ 之间必须再分出一个区间，因为内部字符串种类至少为 $S$。

提几点细节。

1.字符串之间可能有空格。

2.如果是像我一样这么写的：
```cpp
        getline(cin,s);
        ...
        for(int i = 2;i <= q;i ++) {
            ...
        }
        ...
```
不要忘了：
```cpp
        if (q == 0) {//被卡了2天 QAQ
            cout << "Case #" << t << ": 0\n";
            continue;
        }
```
若果 $Q = 0$，你读取引擎 $a_1$ 会……

完整代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1050;
int T,n,a[N],g,v[N],cnt,k,ans,q;
string s;
int main () {
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin >> T;
    for(int t = 1;t <= T;t ++) {
        cin >> n;
        map <string,int> p;
        cnt = 0;
        getline(cin,s);//吃掉'\n'
        for(int i = 1;i <= n;i ++) {
            getline(cin,s);
            p[s] = ++ cnt;
        }
        cin >> q;
        if (q == 0) {
            cout << "Case #" << t << ": 0\n";
            continue;
        }
        getline(cin,s);//吃掉'\n'
        getline(cin,s);//读入引擎
        a[1] = p[s];
        k = 1,ans = 0,g = 1;
        v[a[1]] ++;
        for(int i = 2;i <= q;i ++) {
            getline(cin,s);
            a[i] = p[s];
            if(!v[a[i]]) g ++;
            v[a[i]] ++;
			if(g == cnt) {
			    g = 1;
			    ans ++;
			    while(k < i) v[a[k]] --,k ++;
			    continue;
			}
        }
		while(k <= q) v[a[k]] --,k ++;
        cout << "Case #" << t << ": " << ans << '\n';
    }
    return 0;
}
```

---

## 作者：lcliruiyan (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P13454)

## 题目思路

由于数据很小，我们考虑用暴力模拟的方法来做。

对于每组数据，可以使用一个变量 $p$ 存储当前正在处理的查询。然后枚举第 $p$ 到 $q$ 个查询中有没有与搜索引擎重名的，记录下第一次出现重复的位置。

接着再使用一个变量 $maxt$ 维护重名位置的最大值，然后将答案加 $1$，令当前位置 $p$ 等于 $maxt$。当当前位置 $p$ 大于总查询数量 $q$ 时，退出循环，输出答案。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s,q,ans;
string s1[105],s2[1005];
int main()
{
    cin>>n;
    for(int t=1;t<=n;t++)
    {
        cin>>s;
        cin.ignore();
        for(int i=1;i<=s;i++)
            getline(cin,s1[i]);
        cin>>q;
        cin.ignore();
        for(int i=1;i<=q;i++)
            getline(cin,s2[i]);
        int p=1;
        ans=0;
        while(p<=q)
        {
            int maxt=0;
            for(int i=1;i<=s;i++)
            {
                int j=p;
                while(j<=q&&s1[i]!=s2[j])j++;
                if(j>q)j=q+1;
                if(j>maxt)maxt=j;
            }
            if(maxt>q)break;
            ans++;
            p=maxt;
        }
        cout<<"Case #"<<t<<": "<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：qiaohaoran123 (赞：0)

## 题意
有 $s$ 个搜索引擎和 $q$ 个搜索内容，一个搜索引擎不能搜索该搜索引擎的名字，问最少要切换多少次搜索引擎。
## 思路
定义一个集合，表示当前可以使用的搜索引擎。每输入一个搜索内容，就将这个搜索内容从集合中删除。如果集合为空，就将这个集合赋值为所有搜索引擎的集合。
集合为空的个数就是答案。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int s,t,q,ans;
string str;
int main(){
	ios::sync_with_stdio(false);
	cin>>t;
	for(int i=1;i<=t;i++){
        set<string>f;//所有搜索引擎
		ans=0;
		cin>>s;
        cin.ignore();//去除多余的换行
		for(int j=1;j<=s;j++){
			getline(cin,str);
			f.insert(str);
		}
        cin>>q;
        cin.ignore();
        set<string>f2(f);
		for(int j=1;j<=q;j++){
			getline(cin,k);
			f2.erase(k);
			if(f2.empty()){
				ans++;
				f2=f;
				f2.erase(k);
			}
		}
		cout<<"Case #"<<i<<':'<<' '<<ans<<'\n';
	}
	return 0;
}
```

---

