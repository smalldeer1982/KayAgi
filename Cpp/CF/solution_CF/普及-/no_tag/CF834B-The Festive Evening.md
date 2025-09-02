# The Festive Evening

## 题目描述

七月底，果冻城堡举行节日晚会！来自王国各地的客人聚集在这里讨论糖果业的新趋势。然而，这里讨论的一些事情不应该向公众披露：这些信息可能会在斯威特兰王国引起不和，以防落入坏人之手。所以有必要不让任何不速之客进来。

果冻城堡有26个入口，上面有从A到Z的大写英文字母。由于安全措施，每个客人都被指定了一个入口，他应该通过这个入口进入城堡。每个入口的门在第一个客人到达前打开，在最后一个客人到达后关闭，最后一个客人应该通过这个入口进入城堡。两位客人不能同时进入城堡。

为了保护入口免受可能的入侵，应为其分配一个糖果警卫。城堡里有k这样的守卫，所以如果打开的门超过k，其中一个就会无人看守！注意一个警卫在他被指派的门关上之前不能离开他的岗位。

Slastyona怀疑晚上可能有不速之客。她知道被邀请的客人进入城堡的顺序，想让你帮她检查一下是否有超过千扇门被打开的时刻。

## 样例 #1

### 输入

```
5 1
AABBB
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
5 1
ABABB
```

### 输出

```
YES
```

# 题解

## 作者：X_Chao_Bai (赞：2)

#### CF的题写多了，第一回康到那么详细的翻译竟然有点发慌（

好了，这题的思路就是要看士兵的移动，首次出现就把士兵挪过去，如果同一个门连续有很多客人，那士兵就不需要挪，如果这扇门没人了，就跑去帮其他的人。把这个模拟做好了就基本上没什么问题了。

好了直接上代码。

### code1：
```cpp
#include<bits/stdc++.h> 
using namespace std;
int n,k,a[26];
string s;
bool p[200];
int main(){
    cin>>n>>k>>s;
    for(int i=0;i<n;++i) ++a[s[i]];//同一扇门的人数累加     
    for(int i=0;i<n;++i){
        --a[s[i]];//减掉这扇门的人数
        if(!p[s[i]]){
            --k;//首次出现要挪士兵    
            p[s[i]]=true;//表示这扇门有士兵看着了
        }
		if(k<0){//人数不够用
			cout<<"YES"<<endl;
			return 0;//直接输出结束
		}
        if(!a[s[i]]) ++k;//这扇门该看的人看完了，去帮其他士兵
    }
    cout<<"NO"<<endl;//最后直接输出
    return 0;
}
```
qwq

---

## 作者：a1a2a3a4a5 (赞：0)

##### [题目：](https://www.luogu.com.cn/problem/CF834B)
- 题意：

1. 我们要输入一个长度为 $ n $ 的字符串，只包含大写字母若干个。在一种大写字母第一次出现时开始计数，直到最后一个这种大写字母出现——表示的是这个字母门打开的时间。例如： ` A B B B A `，我们算的门 $ A $ 的打开时间是从字符串第一位一直到最后一位，门 $ B $ 打开的时间则是从字符串第二位到第四位，求是否在某个时刻，打开的门超过 $ k $ 个，如果超过  $ k $ 个输出 ` YES `，否则输出 ` NO `。
2. 精简版：在长度为 $ n $ 线段上，有许多个区间，在某点上覆盖的区间个数是否大于 $ k $ ，如果任意一点大于 $ k $ 就输出 ` YES `，否则输出 ` NO `。

- 思路

1. 这个题可以直接枚举字符串的每一位，如果一个门打开 $ x $ 就 $ + 1 $，一个门关上 $ x $ 就 $ - 1 $。如果中间开门的数量超过了 $ k $ 就直接输出 ` YES `，结束。否则一直运行到最后输出 ` NO `。

2. 我们求出每个字母出现的次数，这样可以推出现在枚举的是否是这个字母的最后一次，也就是一个区间的右端点。~~防止守卫多领工资。~~

- 问题

1. 你需要在开门的一瞬间，立马算开门次数，因为当遇到门就开一秒的时候并且恰好没有守卫，那么门就没人守。~~守卫就会摸鱼，并且吃到干饭，还会让客人生气，最重要的是~~ 你的程序会 WA。

- 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int n,k,x,c[27],us[27];
int main()
{
        cin>>n>>k>>s;
        for(int i=0;i<s.size();i++) c[s[i]-'A'+1]++;
        //记录每个字母出现的次数。 
        for(int i=0;i<s.size();i++)
        {
            us[s[i]-'A'+1]++;
            //记录在 i 位置前字母出现的次数。 
            if(us[s[i]-'A'+1]==1) x++;
            //如果门刚开，记录开门 
            if(x>k) {cout<<"YES";return 0;}
            //在开门的一瞬间检查守卫够不够，防止门开一秒的情况没有记数。 
            if(us[s[i]-'A'+1]==c[s[i]-'A'+1]) x--;
            //如果某个类型门已经开完了，就不用开了，直接关闭。 
        }
        cout<<"NO";
        return 0;
}
```

---

## 作者：tbdsh (赞：0)

# 题意
[题目传送门](https://www.luogu.com.cn/problem/CF834B)

现在有 $n$ 位客人，$k$ 个守卫。每个客人会从指定编号的门进入。如果一个门有客人进入，那么这个门就需要守卫看守。一扇门的开放时间是从**从这扇门进入的第一个客人到最后一个客人进入**。如果守卫数量不够，那么输出 `Yes`，否则输出 `No`。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;
int n, k;
char s[1000005];
int v[30];
bool m[30];
int main(){
  cin >> n >> k >> s;
  for (int i = 0; i < n; i++){
    v[s[i] - 'A' + 1]++;//预处理每扇门需要进入的客人数量。
  }
  for (int i = 0; i < n; i++){
    v[s[i] - 'A' + 1]--;//每进入一个这扇门需要进入客人的数量减一。
    if (!m[s[i] - 'A' + 1]){//如果进入这扇门的是第一个进入这扇门的客人，那么就给这扇门安排一个守卫。
      k--;
      m[s[i] - 'A' + 1] = 1;
    }
    if (k < 0){//如果守卫数量不够，输出 Yes，然后结束程序。
      cout << "Yes";
      return 0;
    }
    if (v[s[i] - 'A' + 1] == 0){//如果需要进入这扇门的客人数量为 0，那么这扇门将被关上，可使用的守卫加一。
      k++;
      m[s[i] - 'A' + 1] = 0;
    }
  }
  cout << "No";//如果没有出现守卫数量不够的情况，输出 No。
  return 0;
}

```


---

## 作者：_Evergarden_ (赞：0)

### [原题传送门](https://www.luogu.com.cn/problem/CF834B)

------------

## 题目大意


这道题的思路就是如果有一个人首次进入一个门，就要派士兵过去，如果一个门有很多人进入，只需要派一位士兵，如果这扇门没有人在进入，就把看守这扇门的士兵派到其他门去看守，若有人进入一扇没有士兵看守的门，就输出 NO 并结束程序，若一直有士兵看守就输出 YES。

## 思路

用一个数组存储每一个客人进入的门，再用另一个数组判断是否是首次进入，若是，就派过去一个士兵。
若守卫不够用，就输出 YES，否则输出 NO。

## Code

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int N = 1e5 + 10;

int n, k, tot[N];//tot数组存储每一个客人进入的门
string s;
bool vis[N];//vis数组判断是否是首次进入

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);//读入优化
    cin >> n >> k >> s;
    for(int i = 0; i < n; ++ i) {
        ++ tot[s[i] - 'A' + 1];//当前这个门进入的人加一
    }
    for(int i = 0; i < n; ++ i) {
        -- tot[s[i] - 'A' + 1];//进入这个门的人的数量减一
        if(!vis[s[i] - 'A' + 1]) {//若在此之前没有人看守这道门
            -- k;//就派过去一个守卫
            vis[s[i] - 'A' + 1] = 1;//并且把这个门标记为有人看守
        }
        if(k < 0) {//若守卫不够用
            printf("YES\n");//就输出YES
            return 0;//直接结束程序
        }
        if(!tot[s[i] - 'A' + 1]) {//若这个门没有人再进入
            ++ k;//就把守卫派到其他地方
        }
    }
    cout << "NO\n";//若一直有人看守，就输出NO
    return 0;
}
```


---

## 作者：lolsq (赞：0)

### 简要的题意
+ 其实就是找在某一时间，会不会有进门的客人比守卫多的情况。这种时候不速之客就有可能进来

### 我的思路
+ 我们就通过枚举的方法来看一下，求一下每一道门从第一个人到最后一个人进门的时间。然后再来看能否满足题目条件

### 注意点

+ 循环26个时一定要从0开始。

### 我的代码
~~~
#include<bits/stdc++.h>
using namespace std;
char a[1000010];
int cnt;
int b[30],c[30];
int main( )
{
	int n,k;
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)
	{
		
		c[a[i]-'A']=i;
       		if(!b[a[i]-'A'])
		{
			b[a[i]-'A']=i;
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<26;j++)
		{
			if(b[j]==i) 
			cnt++;
			if(cnt>k)
			{
				cout<<"YES";
				return 0;
			}
			if(c[j]==i) 
			cnt--;
		}
	}
	if(cnt<=k) 
	cout<<"NO";
	else 
	cout<<"YES";
	return 0;
}
~~~

---

## 作者：褚橙 (赞：0)

### 思路
其实就是一道模拟题，模拟每一个入口的状态，当已经最后一个客人进入后就可以关闭了，当前的警员可以去其他入口帮忙，否则就要有警员一直待着

代码也较为简单注释在里面了：
###### ~~马蜂较丑轻喷~~
```c
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int a[N],book1[N],book2[N];
//book1记录26个入口总共进入的人数
//book2用来模拟当前26个入口进入的人数
int n,k;
string s;
int main()
{
	cin>>n>>k;
	cin>>s;
	for(int i=0;i<n;i++)
	{
		a[i+1]=s[i]-'A';
		book1[s[i]-'A']++;//记入每个入口的人数
	}
	int ans=0;//清零
	for(int i=1;i<=n;i++)
	{
		book2[a[i]]++;
		if(book2[a[i]]==1&&book1[a[i]]==1)
		//记得特判，一个入口可能总共就一人进入
		{
			if(ans+1>k)
			{
				cout<<"YES"<<endl;
				return 0;
				//输出 YES 直接推出
			}
			//一个人进入后门就会关上，跳过后面特判继续枚举
			continue;
		}
		if(book2[a[i]]==book1[a[i]])
		//入口可以关上了，警员可以去帮忙其他门
		{
			ans--;
		}
		else if(book2[a[i]]==1)
		//从第一人起就要一直要有警员在
		{
			ans++;
		}
		if(ans>k)
		{
			cout<<"YES"<<endl;
			return 0;
			//直接退出
		}
	}
	cout<<"NO"<<endl;
	//前面没有结束就输出 NO
	return 0;
}
```
这样就可以了qwq

---

## 作者：Life_alone (赞：0)

~~翻译异常详细~~

#### 思路：
 
最先让士兵一对一，如果士兵不够就直接输出 YES ,否则就等某一扇门看完了，就让他去帮其他士兵。模拟即可。

好了直接上~~高清无注释~~代码：

#### Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1000010];
int b[110];
int main()
{
	memset(b, 0, sizeof(b));
	memset(a, 0, sizeof(a));
	int n, k;
	string s;
	scanf("%d%d", &n, &k);
	cin >> s;
	for (int i = 0; i < n; i++)
	{
		if (b[s[i] - 'A'] == 0)
			a[i]++;
		b[s[i] - 'A']++;
	}
	for (int i = 0; i < n; i++)
	{
		b[s[i] - 'A']--;
		if (b[s[i] - 'A'] == 0)
			a[i + 1]--;
	}
	int sum = 0, maxn = 0;
	for (int i = 0; i < n; i++)
	{
		sum += a[i];
		maxn = max(maxn, sum);
	}
	if (maxn > k)
		printf("YES\n");
	else
		printf("NO\n");
	return 0;
}
```


---

## 作者：smallpeter (赞：0)

这题思路还是比较好想的

首先记录第 $i$ 个路口需要被糖果警卫守卫时间的起点与终点，将其分别表示为 $l_i$ 和 $r_i$。如果存在某时刻 $t$ 满足 $\sum\limits_{i=1}^{26}[t$ $\ge$ $l_i$ $\And$ $t$ $\leqslant$ $r_i$] $>$ $k$，则无解，反之有解。

思路就这样了上代码。


```
#include<bits/stdc++.h>
using namespace std;

const int N=1e6+10,M=27;

int n,k,l[M],r[M];//l[i],r[i]在题解中已经讲了不再重复 

int f[N];//f[i]记录第i个时刻需要多少糖果警卫 

char s[N];

int main()
{
	memset(l,0x3f,sizeof(l));
	memset(r,0,sizeof(r));
	//记得一定要初始化
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
		int w=s[i]-'A';
		l[w]=min(l[w],i);
		r[w]=max(r[w],i);
	}
	for(int i=0;i<M;i++)
	{
		for(int j=l[i];j<=r[i];j++)
		{
			f[j]++;//第j个时刻需要的糖果警卫数量+1 
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(f[i]>k)//有解 
		{
			printf("YES");
			return 0;
		}
	}
	printf("NO");//无解 
	return 0;
}
```


---

## 作者：Sternenlicht (赞：0)

思路：

用 $door_i$ 表示第 $i$ 扇门的人数，$vis_i$ 表示第 $i$ 扇门是否有士兵。

模拟过程：

1. 将读入数据看作下标，加到 $door$ 数组中。

2. 循环 $n$ 次，先让当前入口减去一个人，若这扇门没人看，则让士兵总数减一，且标记为一。

3. 若没有士兵了，则输出 YES，并结束程序。

4. 若当前门已经没人了，让士兵数加一。

5. 循环结束后，若还没结束程序，输出 NO。

```cpp
#include <bits/stdc++.h>
#define LL long long
#define endl '\n'
#define lowbit(x) (x&-x)
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define INF 0x3f3f3f3f
namespace IO{
	inline LL read(){
	    LL x=0,f=1;char ch=getchar();
	    for (;!isdigit(ch);ch=getchar())if (ch=='-')f=-1;
	    for (;isdigit(ch);ch=getchar())x=(x<<3)+(x<<1)+(ch^48);
	    return x*f;
	}
	inline void write(LL x,char c='\n'){
	    if (x){
	    	if (x<0)x=-x,putchar('-');
	    	char a[30];short l;
	    	for (l=0;x;x/=10)a[l++]=x%10^48;
	    	for (l--;l>=0;l--)putchar(a[l]);
		}
		else putchar('0');putchar(c);
	}
	inline char getc(){
		char ch=getchar();
		while (isspace(ch))ch=getchar();
		return ch;
	}
}
using namespace IO;
using namespace std;

const int N = 200;
int door[N],vis[N];//door标记每扇门的人数，vis[i]表示第i扇门有士兵 
string s;
int main(){
	int n=read(),k=read();cin>>s;
	for (int i=0;i<n;i++)door[s[i]]++;//这扇门的人数+1
	for (int i=0;i<n;i++){
		door[s[i]]--;//减去进去的一个人 
		if (!vis[s[i]])k--,vis[s[i]]=1;//这扇门没人看，标记，士兵-1
		if (k<0)return puts("YES"),0;//没有士兵了，说明没有不速之客
		if (!door[s[i]])k++;//这扇门没人了，让士兵+1 
	}
	puts("NO");//循环退出后，说明有人在无士兵的情况下进了门，输出NO 
	return 0;
}
```

---

## 作者：GalaxyOier (赞：0)

 [更好的阅读体验](https://www.luogu.com.cn/blog/361069/solution-cf834b)
# 思路
我的思路思维难度较低


>首先记录每一个入口的宾客人数。
>
>再按照时间顺序，每进入一个就记录一下，等到该入口所有的人都进去之后，就有一个守卫空出来。
>
>不断进行此操作就可以啦。


说的比较生硬，可以参考代码理解
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k;
int cnt1[26] = {0}, cnt2[26] = {0};
//cnt1[i]记录从i号入口进入的宾客数
//cnt2[i]按时间顺序记录经过人数 
char c[1000001];
int chg(char c) {
	//将大写字符转化为数字 
	return (int)c - 64;
	//A的ASCLL码为65，以此类推 
}
bool chk() {
	//检测当前需要守卫的入口数是否大于守卫人数
	int sum = 0;//当前需要守卫的入口数 
	for (int i = 1; i <= 26; i++) {
		if (cnt2[i]) sum++; 
	} 
	if (sum > k) return true;
	//确实大于，返回真 
	else return false;
	//守卫还能应付得来，返回假 
} 
void debug() {
	for (int i = 1; i <= 26; i++) {
		if (cnt1[i]) {
			cout << cnt1[i] << " " << cnt2[i] << endl;
		}
	}
}
int main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> c[i]; 
		cnt1[chg(c[i])]++;
	}
	for (int i = 1; i <= n; i++) {
		cnt2[chg(c[i])]++;
		//对应入口经过人数加1 
		if (cnt2[chg(c[i])] == cnt1[chg(c[i])]) {
			cnt2[chg(c[i])] = 0;
			//当该入口的宾客已经全部进入 
			//就不再需要守卫了 
		}
//		debug();
		if (chk()) {
			cout << "YES";
			return 0;
		}
	}
	cout << "NO";
	return 0;
}
```

---

## 作者：qian_shang (赞：0)

**[题目传送门](luogu.com.cn/problem/CF834B)**

本题的想法是：模拟+字符串操作

具体思路如下：

1. 找到每个字母的最后出现位置
1. 把字符串从头到尾扫一遍，遇到新字母就个数加一
1. 如果个数超过限制则输出$NO$
1. 遇到每个字母的最后位置就个数减一

详见代码
```
#include<bits/stdc++.h>
#define N 30
#define M 1000005
using namespace std;
int n,m,last[N],sum;//last为每个字母的最后位置
char c[M];
bool vis[N];//新字符有没有出现
int main(){
	scanf("%d%d",&n,&m);
	scanf("%s",c+1);//读入
	for (int i=1;i<=n;i++) last[c[i]-'A']=i;//统计最后位置直接覆盖
	for (int i=1;i<=n;i++){
		if (!vis[c[i]-'A']){
			vis[c[i]-'A']=1;
			sum++;//遇到新字母累计个数
			if (sum>m){printf("YES");return 0;}//超过限制直接退出
		}
		if (i==last[c[i]-'A']) sum--;//遇到末尾位置个数减一
	}
	printf("NO");//没超过限制
   return 0;
}
```


---

