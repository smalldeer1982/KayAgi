# Mahmoud and Ehab and the message

## 题目描述

小A想要给他的朋友小B发送了一条有 $m$ 个单词的消息。他们的语言由编号从 $a_1$ 到 $a_n$ 的 $n$ 个单词组成。一些单词具有相同的意思，因此存在 $k$ 个单词组，其中每个组中的所有单词具有相同的意思。小A知道第 $i$ 个单词可以以成本 $m_i$ 发送。

对于他的每个消息中的单词，小A可以将其替换为具有相同意思的另一个单词，或者保持不变。请帮助小A确定发送消息的最小价值。

发送消息的成本是其中每个单词的发送成本的总和。

## 样例 #1

### 输入

```
5 4 4
i loser am the second
100 1 1 5 10
1 1
1 3
2 2 5
1 4
i am the second
```

### 输出

```
107```

## 样例 #2

### 输入

```
5 4 4
i loser am the second
100 20 1 5 10
1 1
1 3
2 2 5
1 4
i am the second
```

### 输出

```
116```

# 题解

## 作者：sqrt404 (赞：3)

## 题面描述：

$n$ 个单词，每个单词有自己的价值，$k$ 组一样意思（价值不同）的单词组，最后用前面的 $n$ 个单词组成一句话，并替换一些有相同词义的词的单词，然后算出这句组成的话的最小的所需要的价值。

## 思路：

模拟，然后输入的时候就提前进行计算。

## 过程：
1. 将信息写入 $str$ 和 $strn$
2. 替换相同词义的单词的价值
3. 进行句子价值的计算

## 参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
struct word // 储存词库
{
    int money;// 价值
    string name;// 储存名字，主要是为了下面的序号与单词的对应
};
int n, k, m, gg;// n，k，m意思如题所示，gg是用来输入下面的k组相同词义的单词的
map<string, word> str;
map<int, word> strn;
string bala[100005], sentens[100005];
// 这里解释一下 str和strn都是word类型的数据，一个下标是序号，另一个是单词。bala是下面用来储存单词的，sentens（英语不好别怪我）是用来最后输入需要的单词的
int main()
{
    cin >> n >> k >> m;
    for(int i = 1; i <= n; i++) cin >> bala[i];
    for(int i = 1; i <= n; i++)
    {
    	cin >> str[bala[i]].money;
    	strn[i].name = bala[i];// 将名字储存到strn，后面要进行编号与单词的转换
	}
    for(int i = 1; i <= k; i++)
    {
        cin >> gg;
        if(gg == 1) // gg = 1时就没必要计算了
        {
            int hh; // 没用，只是用来输入时格式化
            cin >> hh;
        }
        else
        {
        	int same[100005];
            for(int j = 1; j <= gg; j++) cin >> same[j];
            int flag = str[strn[same[1]].name].money; // 打擂台
            for(int j = 1; j <= gg; j++) flag = min(flag, str[strn[same[j]].name].money);
            for(int j = 1; j <= gg; j++) str[strn[same[j]].name].money = flag;// 将所有同义词的价值都改成这些同义词中最小的价值
        }
    }
    unsigned long long sum = 0;//必须用unsigned long long，不然会超
    for(int i = 1; i <= m; i++)
    {
    	cin >> sentens[i];
    	sum += str[sentens[i]].money;
	}
	cout << sum << endl;
    return 0;
}
```

---

## 作者：zzhbpyy (赞：1)

### [原题传送门](https://www.luogu.com.cn/problem/CF959B)

## 思路

将每组的所有单词编号分别存入 vector 数组，并按照每个单词成本的从小到大进行排序。开一个 unordered_map 记录每个单词的组号。然后读入 Mahmoud 发送的消息中的每一个单词，将对应组别的最小成本累加到 $ans$ 中即可。

## 完整代码

```c++
#include<bits/stdc++.h>
#define int long long//不开longlong见祖宗
using namespace std;
struct G{
	string a;
	int b; 
}a[100005];
int n,k,m,c,tmp;
vector<int>aa[100005];
unordered_map<string,int>mp;
signed main(){
	cin>>n>>k>>m;
	for(int i=1;i<=n;i++)cin>>a[i].a;
	for(int i=1;i<=n;i++)cin>>a[i].b;
	for(int i=1;i<=k;i++){
		cin>>c;
		while(c--){
			cin>>tmp;mp[a[tmp].a]=i;//a[tmp].a的组号为i
			aa[i].push_back(tmp);
		}
		sort(aa[i].begin(),aa[i].end(),[](int c,int d){return a[c].b<a[d].b;});//Lambda表达式
	}
	string d;int ans=0;
	while(m--){
		cin>>d;
		ans+=a[*(aa[mp[d]].begin())].b;//取最小成本
	}
	cout<<ans;
}
```

---

## 作者：Zhuluoan (赞：0)

## 题目简述

小 A 想要给他的朋友小 B 发送了一条有 $m$ 个单词的消息。他们的语言由编号从 $a_1$ 到 $a_n$ 的 $n$ 个单词组成。一些单词具有相同的意思，因此存在 $k$ 个单词组，其中每个组中的所有单词具有相同的意思。小 A 知道第 $i$ 个单词可以以成本 $m_i$ 发送。

对于他的每个消息中的单词，小 A 可以将其替换为具有相同意思的另一个单词，或者保持不变。请帮助小 A 确定发送消息的最小价值。

发送消息的成本是其中每个单词的发送成本的总和。

## 题目分析

对于单词 $s$，我们一定会将 $s$ 换成它所在的组中价值最低的一个，依据此贪心思路模拟即可。

具体而言，可以先用一个 `map` 将单词与编号对应起来，再在输入单词组时更新每个组的最小值，同时记录各个单词是属于哪一个单词组的，最后遍历每一个单词，将答案累加它所在的组的最小值。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define random(a,b) (rand()%(b-a+1)+a)
#define se second
#define fi first
#define pr pair<int,int>
#define pb push_back
#define ph push
#define ft front
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,a,b) for(int i=a;i>=b;i--)
#define mem(a,b) memset(a,b,sizeof a)
const int N=1e5+10; 
int n,k,m,vis[N],x,Min[N];
ll ans;
string q;
map<string,int> Vis;
struct word
{
	string s;
	int val;
}a[N];
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>k>>m;
    mem(Min,0x3f);
	For(i,1,n)
	{
		cin>>a[i].s;
		Vis[a[i].s]=i;
	}
	For(i,1,n)
	{
		cin>>a[i].val;
	}
	For(i,1,k)
	{
		cin>>x;
		int temp=0;
		while(x--)
		{
			cin>>temp;
			vis[temp]=i;
			Min[i]=min(Min[i],a[temp].val);
		}
	}
	For(i,1,m)
	{
		cin>>q;
		ans+=Min[vis[Vis[q]]];
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：小闸蟹 (赞：0)

```cpp
// 看了一下数据范围，就直接暴力模拟吧
// 虽然过得很不好看，因为运行时间有点长（873ms），但是过了不是（滑稽）
// 具体见代码吧，像这样暴力的话，这题难度大概“普及-”
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

using ll = long long;

ll Pri[100000 + 50], Num[100000 + 50];

ll Read()
{
    ll n = 0;
    char ch = std::getchar();
    while ((ch > '9' || ch < '0') && ch != '-')
    {
        ch = std::getchar();
    }

    while (ch <= '9' && ch >= '0')
    {
        n = n * 10 + ch - '0';
        ch = std::getchar();
    }

    return n;
}

int main()
{
    ll n, k, m;
    std::cin >> n >> k >> m;
    std::unordered_map<std::string, ll> Map;    // <词语名称, 编号>
    std::string Str;
    for (ll i = 1; i <= n; ++i)
    {
        std::cin >> Str;
        Map[Str] = i;   // 记下每个词语的编号
    }

    for (ll i = 1; i <= n; ++i)
    {
        Pri[i] = Read();
    }

    for (ll i = 1; i <= k; ++i)
    {
        ll p, Min = 999999999 + 50;
        p = Read();
        for (ll i = 1; i <= p; ++i)
        {
            Num[i] = Read();
            if (Pri[Num[i]] < Min)  // 记下同类型词语当中花费最小的那个的价格
            {
                Min = Pri[Num[i]];
            }
        }

        for (ll i = 1; i <= p; ++i)
        {
            Pri[Num[i]] = Min;  // 然后只要将同类型的词语的花费全都设为最小的即可
        }
    }

    ll Sum = 0; // 因为同类型的词语的当前花费都变成最小的了，所以直接查询目前词语就好了
    for (ll i = 1; i <= m; ++i)
    {
        std::cin >> Str;
        Sum += Pri[Map[Str]];
    }

    std::cout << Sum << std::endl;

    return 0;
}
```

---

