# Swaps

## 题目描述

There are $ n $ players sitting at a round table. All of them have $ s $ cards of $ n $ colors in total. Besides, initially the first person had cards of only the first color, the second one had cards of only the second color and so on. They can swap the cards by the following rules:

- as the players swap, a player can give a card of his color only;
- a player can't accept a card of a color he already has (particularly, he can't take cards of his color, no matter whether he has given out all of them or not);
- during one swap a pair of people swaps cards (each person gives one card and takes one card).

The aim of all $ n $ people is as follows: each of them should give out all the cards he had initially (that is, all cards of his color). Your task is to denote whether such sequence of swaps is possible. If the answer is positive, you should list all the swaps.

## 样例 #1

### 输入

```
4 8
2 2 2 2
```

### 输出

```
Yes
4
4 3
4 2
1 3
1 2
```

## 样例 #2

### 输入

```
6 12
1 1 2 2 3 3
```

### 输出

```
Yes
6
6 5
6 4
6 3
5 4
5 3
2 1
```

## 样例 #3

### 输入

```
5 5
0 0 0 0 5
```

### 输出

```
No
```

# 题解

## 作者：CASSINI_Thx (赞：2)

# Solution CF134C Swaps
[题目传送门]: https://www.luogu.com.cn/problem/CF134C

#### 前置芝士：

1. bfs搜索
2. 结构体
3. 优先队列
4. *pair(可会可不会，不强求)

#### 题目翻译：

$n$个人围成一圈按照给定规则交换所持卡牌。如若存在一种换法，使交换后没有人手上有自己的初始卡牌，就输出$Yes$，并输出换牌步骤，否则输出$No$。

#### 分析：

首先，我们可以通过分析题意，判断一些无需计算可以直接输出$No$的情况：
1.由于每个人最多只可以有某颜色卡牌一张，因而一旦有人初始卡牌数量大于等于总人数，就可以直接判断无解。
2.由于每次交换时都是两张牌同时发生变化，且任何人无法拿到自己的初始卡牌，因而但凡卡牌数为奇数，也可以直接判断无解。

接着我们就可以用~~暴力~~朴素的bfs搜索进行模拟，模拟整个交换过程。我们每次都选择当前未交换卡牌最多的人进行交换，这个部分用优先队列就可以很完美地实现。因为交换时总是两张卡牌一组，我们可以用stl中的pair来实现，当然不会也没有关系，也可以自定义一个结构体来实现，效果是一样的。~~只是既然都已经做到这道题了，遇见即是缘，dalao您真不考虑学一点新东西么qwq。~~至于换牌的步骤，我们同样可以用pair或结构体实现，详见代码。

为同时展示结构体和pair的用法，本蒻码的code中各用了一个，各位可以根据需要食用。

#### Code

又到了我们喜闻乐见的code环节了呢。

码风不好，见谅。

```cpp
#include<bits/stdc++.h>
#define int long long	//避免见祖宗神器,但使用后int main应改为signed main 
#define re register int	//一点常数小优化,但其实并没有什么用,可忽略 
using namespace std;
const int N=200010;
int n,s; //意义如题 
int tot=1; //表示步骤总数 
bool flag=1;
struct ty
{
	int val,id;	
    bool operator<(ty a)const	//结构体实现优先队列
    {
        return val<a.val;
    } 
}st,en,num[N];
priority_queue<ty> q;	//定义优先队列
typedef pair<int,int>cards; //定义pair的类型 
cards ans[N]; 
inline int qr() //快读板子,此题非必要
{
	int a=0,f=1;
	char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		a=(a<<1)+(a<<3)+(ch^48);
		ch=getchar();
	}
	return a*f;
}
inline void putout(int a) //快输板子,此题非必要
{
	if(a<0)
	{
		a=~(a-1);
		putchar('-');
	}
	if(a>9) putout(a/10);
	putchar(a%10+48);
}
void pre() //预处理读入和直接判断无解的情况 
{
		n=qr(),s=qr();
	if(s&1) //违反规律2
	{
		puts("No");
		exit(0);
	}
	for(re i=1;i<=n;i++)
	{
		int a=qr();
        if(a>=n) flag=0; //如果卡牌数量大于等于总人数,修改标记 
        st.val=a;
		st.id=i;
        if(st.val>0) q.push(st); 
	}
	if(!flag) //违反规律1 
    {
		puts("No");
		exit(0);
    }
} 
void write() //判断与输出 
{
	if(!flag)
    {
    	puts("No");
        exit(0);
    }
    puts("Yes");
    printf("%lld\n",s/2);
    for(re i=1;i<=tot;++i)
		printf("%lld %lld\n",ans[i].first,ans[i].second);
} 
signed main()
{
	pre();
    while(q.size())
    {
        st=q.top();
        q.pop();
        if(q.size()<st.val) //队列的中最大卡牌数大于总人数,修改标记 
        {
            flag=0;
            break;
        }
        for(re j=0;j<st.val;j++) //交换ing 
        {
            en=q.top();
            q.pop();
            num[j].id=en.id;
            num[j].val=en.val;
            num[j].val--;
            ans[tot].first=st.id; //记录换牌方案 
            ans[tot++].second=num[j].id;
        }
        for(re j=0;j<st.val;++j)
            if(num[j].val>0) q.push(num[j]); //未交换则入队
    }
    write();
	return 0;
}
```

完结撒花花~ 希望大家能有所收获。

---

## 作者：JCLinux (赞：1)

## 题意理解：
每个人都要与 $a_i$ 个人交换手牌，为了达到这一目的，我们必须要保证，对于为个人，要有**足够多的人能与之交换手牌**。

只有手里还握有自己原有的牌的人才能与别人交换手牌。

那么我们要做的就是尽量保证**有原有手牌**的人最多即可。

问题转化成了怎么让有原有手牌的人最多。

显然，**贪心地**让原有手牌最多的人与原有手牌次多的 $a_i$ 个人交换即可，这样能尽可能多得保留更多有原有手牌得人。

由于每次交换完成之后，每个人的原有手牌数量会发生变化，因此优先队列（大根堆）非常适合这个工作，再一看牌的数量  $2e^5$ 完全没问题。

这个题还有一个坑就是注意 $a_i=0$ 这种特殊情况，要加入特判过滤掉。

## 上代码:

```cpp
using namespace std;
int n,t;
struct node//因为答案要我们输出人员之间的交换记录，要用结构体存储人员编号
{
    int i;
    int val;
    bool operator<(node b) const
    {
        return val<b.val;
    }
};
node cache[200005];
pair<int,int> ans[200005];
priority_queue<node , vector<node> > q;
int main()
{
    cin.sync_with_stdio(false);//能大大加快输入速度
    cin >> n >> t;
    for(int i=1;i<=n;i++)
    {
        int tmp;
        cin >> tmp;
        if(tmp)q.push(node{i,tmp});//注意0不应该被加入优先队列，我在第45个测试点wa一次就是因为这个
    }
    int num=0;
    while(!q.empty())
    {
        node a=q.top();
        q.pop();
        if(a.val>(int)q.size())//如果手中自己颜色排数最多的那个人的排数比剩下的人的都多，不可能交换完成
        {
            cout << "No" ;
            return 0;
        }
        for(int i=1;i<=a.val;i++)//贪心策略：与自己颜色手牌最多的人交换，每个人交换一个排
        {
            cache[i]=q.top();//先把这些人暂存起来
            cache[i].val--;
            ans[++num].first=a.i;//记录交换情况，这就是答案
            ans[num].second=cache[i].i;
            q.pop();
        }
        for(int i=1;i<=a.val;i++)
        {
            if(cache[i].val) q.push(cache[i]);//注意，交换完之后，还有手牌的人重新入列
        }
    }
    cout << "Yes" << endl << num << endl;//答案输出
    for(int i=1;i<=num;i++)
    {
        cout << ans[i].first << " " << ans[i].second << endl;
    }
    return 0;
}

```


---

