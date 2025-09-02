# Zebras

## 题目描述

给你一个01串，要求将它划分成多个子序列，子序列不一定是连续的，子序列要满足以0开头，以0结尾，中间01交替出现。

## 样例 #1

### 输入

```
0010100
```

### 输出

```
3
3 1 3 4
3 2 5 6
1 7
```

## 样例 #2

### 输入

```
111
```

### 输出

```
-1
```

# 题解

## 作者：pushinl (赞：6)

题目大意就是给你一段0/1串，找0 1交替出现的子串 输出每个子串长度和在原串的位置.

每个子串以0开头，以0结束.

所以很容易得到：0的个数必须比1多.

我们设置一个统计数量的变量cnt.

由于不知道子串个数，害怕炸空间，就不能用二维数组.应该用二维的动态数组vector.~~反正我这样叫~~

先输入 然后扫一遍，遇到0 cnt++，并且把0的位置压进数组.遇到1 cnt--，并把1的位置压进数组.因为遇到0后再遇到1 cnt的值不会变，所以此时的子串0和1的位置就放到了数组的cnt这同一行上.如果cnt比0小直接输出-1.

上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[200005];
int l,cnt,k;
vector<int>q[200005];//二维动态数组 
int main(){
    scanf("%s",s);
    l=strlen(s);
    for(int i=0;i<l;i++){
        if(s[i]=='0')q[cnt++].push_back(i+1);	//0
        else{									//1
            if(cnt==0){			//如果1比0多就不可能满足条件 
                cout<<-1<<endl;
                return 0;
            }
            q[--cnt].push_back(i+1);
        }
        k=max(k,cnt);
    }
    if(cnt!=k){
        cout<<-1<<endl;
        return 0;
    }
    cout<<cnt<<endl;
    for(int i=0;i<cnt;i++){
        cout<<q[i].size();//输出个数
        for(int j=0;j<q[i].size();j++)
            cout<<" "<<q[i][j];//输出位置
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：One_JuRuo (赞：1)

## 思路

我们可以先模拟一下：

如果发现该位为 $1$，那么只能将这一位放在目前末位是 $0$ 的子序列。如果不存在，则无解；

如果发现该为为 $0$，那么要么将这一位放在目前末位是 $1$ 的子序列，要么新开一个子序列，并放在首位。

如果最后存在子序列的末位是 $1$ 在该种分法不合理，因为没有要求子序列的个数，所以可以采取贪心策略，尽可能的减少末位 $1$ 的子序列个数，如果当前为 $0$ 且存在末位为 $1$ 的子序列，则放在该子序列的末位，不存在，才新开一个子序列。

我们可以用一个变量 $cnt$ 储存目前的子序列个数，用一个变量 $num$ 储存目前末位为 $1$ 的子序列个数。

每次遇到 $1$ 就把 $1$ 放在第 $num+1$ 个子序列的末位，如果 $num=cnt$ 则代表非法。

每次遇到 $0$ 则把 $0$ 放在第 $num$ 个子序列的末位，如果 $num=0$ 则代表需要新开一个子序列。

最后判断 $num$ 是否为 $0$ 就可以判断能否划分了。

然后思考如何输出方案，可以使用 vector 储存每个子序列的情况。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int cnt,num,n;
vector<int>v[200005];
char s[200005];
int main()
{
	scanf("%s",s),n=strlen(s);
	for(int i=0;i<n;++i)
	{
		if(s[i]=='1')
		{
			if(num==cnt) printf("-1"),exit(0);
			v[++num].push_back(i);
		}
		else
		{
			if(num) v[num--].push_back(i);
			else v[++cnt].push_back(i);
		}
	}
	if(!cnt||num) printf("-1"),exit(0);
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;++i)
	{
		printf("%d",v[i].size());
		for(int j=0;j<v[i].size();++j) printf(" %d",v[i][j]+1);//存的时候少1，这里加回来
		puts("");
	}
	return 0;
}
```

---

## 作者：_775spacing747_ (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF949A)
# 题目大意
给你一段 $01$ 串，请你找出所有 $01$ 交替的子串，输出每个子串的**长度**和在原串的**位置**。
# 解法思路
我们设一个 vector 用来存储答案，每次如果是 $0$，就存在末尾是 $1$ 的里面，如果是 $1$，就存在末尾是 $0$ 的里面，用一个变量 $k$ 来控制下标。
# CODE

```cpp
#include<bits/stdc++.h>
#define int long long//开不开long long都行 
using namespace std;
vector<int>v[200005];//定义一个vector来存储答案 
signed main()
{
	int k=0,ma=0;
	string s;
    cin>>s;
    s=' '+s;//给string前面加一个空格，使下标从1开始 
    //v是按照i的末尾是1,i+1的末尾是0,i+2的末尾是1......交叉排列 
    for(int i=1;i<s.size();i++)
	{
        if(s[i]=='0')v[++k].push_back(i);//是0,就k++，插在下一个是1的后面 
        else//是1 
        {
        	if(k==0)//因为第一个要是0，如果k==0,说明没有，即输出-1 
			{	
                cout<<-1<<endl;
                return 0;
            }
            v[--k].push_back(i);
			/*是1,就k--，插在上一个0的后面
            不能k++,因为不确定后面有没有，没有的话那新的序列第一个就为1了 
            */
		}
        ma=max(ma,k);//取下最大值 
    }
    if(k!=ma)//如果k最后不是最大值，说明序列还有剩余，因为末尾也要是0，所以最后一定会重新变成最大值 
	{
        cout<<-1<<endl;
        return 0;
    }
    cout<<k<<endl;//输出个数 
    for(int i=1;i<=k;i++)
	{
        cout<<v[i].size()<<" ";//输出长度 
        for(int j=0;j<v[i].size();j++)cout<<v[i][j]<<" ";//输出位置 
        cout<<"\n";//换行
    }
    return 0;
}
```
### [AC记录](https://www.luogu.com.cn/record/169682703)

---

## 作者：lskksl (赞：0)

这个题的思路非常巧妙。我们首先需要换一个角度去看拆分问题：

观察发现凡 ```awesome``` 的串都是 $0$ 开始，$0$ 结尾，中间 $01$ 交替；并且 ```awesome``` 的串之后是可以再添加一些 $10$ 继续 ```awesome``` 的。

并且对于所有的 ```awesome``` 的串，后面应当添加的内容是与前面无关的。

所以我们从左向右扫这个字符串，并且记录前面有多少个子序列是 $0$ 结尾 ```ct0```，有多少个是 $1$ 结尾 ```ct1```。如果扫到一个 $0$，就 ```--ct1```
，```++ct0```；如果扫到一个 $1$ ，则```--ct0```，```++ct1```。如果 ```ct1``` 减到 $0$ 了就不再减，相当于新开一个子序列；如果 ```ct0``` 减到负数那就无解，最后还有 ```ct1``` 也是无解。

---

## 作者：JiaY19 (赞：0)

前置知识 vector。

不会的[点这里](https://oi-wiki.org/lang/csl/sequence-container/)。

#### 题目大意

给你一个01串，需要拆分成很多个以0开头且以0结尾的01串。

我们可以用一个 vector 容器来储存这些拆分好的01串。

需要用一个 cnt 变量来进行维护。

这个变量是用来统计0的数量，如果有0，它就加一，如果有1，它就减一。

当变量变为负数，就直接判不成立。

#### 一些细节

这里需要注意，当循环结束以后， cnt 若是不等于 vector 的数量，也需要判不成立（这里还卡了我一次）。

#### Code

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int cnt , tot , i;
char a;
vector<int> c[1000000];

signed main()
{
	while(cin >> a)
	{
		i++;
		if(a == '0') c[cnt].push_back(i) , cnt++ , tot = max(tot , cnt);
		else 
		{
			cnt--;
			if(cnt < 0)
			{
				cout << -1;
				return 0;
			}
			c[cnt].push_back(i);
		}
	}
	if(tot != cnt)
	{
		cout << -1;
		return 0;
	}
	cout << tot << endl;
	for(int i = 0;i < tot;i++)
	{
		cout << c[i].size() << " ";
		for(int j = 0;j < c[i].size();j++) cout << c[i][j] << " ";
		cout << endl;
	}
	return 0;
}

```

完结撒花！


---

## 作者：20160161simon (赞：0)

这道题应该是有很多做法，这里介绍一种STL做法。

首先说下整体思路~~其实也没什么思路~~，整体上是个模拟题，先建个 vector 的数组然后遍历原字串：

如果是 $0$ 就去找 vector 数组中最前面的一个末位为 $1$ 的 vector 补上，否则就新建一个数组。

如果是 $1$ 就去找 vector 数组中最前面的一个末位为 $0$ 的 vector 补上，如果找不到就直接输出 $-1$ 。

说下怎么实现上述算法。

本蒟蒻是用 set 实现的，建立两个 set ，一个表示 0 结尾的 vector 下标集合，一个表示 $1$ 结尾的 vector 下标集合。

然后就直接用 ```*(set.begin())``` 取出最小的下标就行。(这是一个 $O(1)$ 的操作)

具体代码如下:

```cpp
#include <bits/stdc++.h>
#define DEBUG
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
ll read(){
	char c=getchar();bool flag=0;ll x=0;
	while(c<'0'||c>'9'){if(c=='-')flag=1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-'0';c=getchar();}
	return flag?-x:x;
}
const ll N=2e5+10;
char s[N];
vector<ll> p[N];
set<ll> mrk[2]; 
int main(){
	scanf("%s",s+1);
	ll len=strlen(s+1),top=0;
	for(ll i=1;i<=len;i++){
		if(s[i]=='0'){
			if(!mrk[1].size()){
				p[++top].push_back(i); 
				mrk[0].insert(top);
			}
			else{
				p[*(mrk[1].begin())].push_back(i);
				mrk[0].insert(*(mrk[1].begin()));
				mrk[1].erase(mrk[1].begin());
			}
		}
		else{
			if(!mrk[0].size()){
				printf("-1\n");
				return 0;
			}
			else{
				p[*(mrk[0].begin())].push_back(i);
				mrk[1].insert(*(mrk[0].begin()));
				mrk[0].erase(mrk[0].begin());
			}
		}
	}
	if(mrk[1].size()) printf("-1\n");
	else{
		printf("%lld\n",top);
		for(ll i=1;i<=top;i++){
			printf("%lld ",p[i].size());
			for(ll j=0;j<p[i].size();j++) printf("%lld ",p[i][j]);
			printf("\n");
		}
	}
}

```


---

