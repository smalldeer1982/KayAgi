# [ABC005C] おいしいたこ焼きの売り方

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc005/tasks/abc005_3

 高橋君は、たこ焼きをどの順番で売るか悩んでいました。というのも、作り置きされたたこ焼きは美味しくないとわかっているので、高橋君はそのようなたこ焼きを売りたくないのですが、できたてばかり売ってしまうと売れるたこ焼きの数が減ってしまいます。

 また、お客さんを待たせてばかりだと、次第にお客さんが離れてしまうだろうと高橋君は考えています。  
 そこで、彼は $ T $ 秒以内に作成されたたこ焼きを売り続けることで、お客さんを捌ききれるかどうかを調べることにしました。

 たこ焼きは $ A_1 $、$ A_2 $、…、$ A_N $ 秒後に焼きあがります。  
 お客さんは $ B_1 $、$ B_2 $、…、$ B_M $ 秒後にやってきます。  
 $ 1 $ 人のお客さんに対して、たこ焼きを $ 1 $ つ売るとします。すべてのお客さんにたこ焼きを売れるなら`yes`、売れないなら`no`を出力して下さい。

 入力は以下の形式で標準入力から与えられる。 > $ T $ $ N $ $ A_1 $ $ A_2 $ $ ... $ $ A_N $ $ M $ $ B_1 $ $ B_2 $ $ ... $ $ B_M $

1. $ 1 $ 行目に、何秒以内のたこ焼きまで売るかを表す整数$ T(1≦T≦100) $が与えられます。
2. $ 2 $ 行目に、高橋君が作成するたこ焼きの総数を表す整数$ N(1≦N≦100) $が与えられます。
3. $ 3 $ 行目に、それぞれのたこ焼きが何秒後にできるかを表す整数 $ Ai(1≦Ai≦100、A1≦A2≦...≦AN) $ が半角スペース区切りで $ N $ 個与えられます。
4. $ 4 $ 行目に、来店するお客さんの人数を表す整数$ M(1≦M≦100) $が与えられます。
5. $ 5 $ 行目に、それぞれのお客さんが何秒後に来るかを表す整数 $ Bi(1≦Bi≦100、B1≦B2≦...≦BM) $ が半角スペース区切りで $ M $ 個与えられます。

 すべてのお客さんにたこ焼きをすぐ売れるなら`yes`、売れないなら`no`を出力して下さい。

 また、出力の末尾には改行を入れて下さい。

# 题解

## 作者：精神小伙！ (赞：8)

## 概括题意：

你现在正在做章鱼烧，章鱼烧会在 $ T $ 秒后过期，你不能让买家等你，如果**章鱼烧过期就不能卖**，求能不能全部卖完。



## 输入：

第一行输入一个 $ T $ 代表章鱼烧的保质期，也就是说章鱼烧放置的**超过 $ T $ 秒就算过期，不能卖了**。

第二行输入一个 $ n $ 代表章鱼烧的数量。

第三行输入从 $ a_1 $ 到 $ a_n $ 的 $ n $ 个正整数，代表每个章鱼烧做出来的时间。

第四行输入一个 $ m $ 代表客人的数量。

第五行输入从 $ b_1 $ 到 $ b_m $ 的 $ m $ 个正整数，表示每个客人来的时间。



## 思路：

这道题暴力枚举就可以了。

首先先判断如果客人的数量大于章鱼烧的数量，说明肯定卖不完（章鱼烧数量不够），直接输出```no```。

判断完毕后把客人来的时间和章鱼烧做出来的时间**从小到大排序**，因为输入的数据不一定是单调递增的。

接下来开始枚举，每次都卖时间最早做出来的章鱼烧（否则卖后面的会过期），有几个条件：

- **没有过期**，即做出来的时间不能超过 $ T $ 秒。


- **做出来的时间比客人来的时间要早**。

注意，这里并**没有判断章鱼烧有没有卖过**这个条件，因为从小到大排序枚举后不会出现这种情况，不理解的话可以看下面的代码部分。

如果章鱼烧都卖完了但是还有客人没吃到章鱼烧就输出```no```。

否则输出```yes```。



## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int a[100010],b[100010];
int main()
{
	int n,t,m,y=1;
	cin>>t;
	cin>>n;
	for(int i=1;i<=n;++i)
	    cin>>a[i];
	cin>>m;
	for(int i=1;i<=m;++i)
	    cin>>b[i];
	if(m>n)//客人的数量大于章鱼烧的数量
	{cout<<"no"<<endl;return 0;}//直接输出no
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);//从小到大排序
	for(int i=1;i<=m;++i)
	{
		bool x=0;
		for(int j=y;j<=n;++j)//枚举没买过的章鱼烧
		{
			if(a[j]<=b[i]&&a[j]+t>=b[i])//满足条件卖出 
			{
				x=1;
				y=j+1;//前面的章鱼烧都不能用了，从下一个开始卖，加上这句就不会有重复的章鱼烧卖出
				break; 
			}
		}
		if(!x){cout<<"no"<<endl;return 0;}//卖不出去，直接输出no 
	}
	cout<<"yes"<<endl;//每位客人都能卖出去 
	return 0;
}
```

如果你看懂了可以点击[传送门](https://www.luogu.com.cn/problem/AT821)去试一试做的对不对。

---

## 作者：sudaJones (赞：3)

[题目地址](https://www.luogu.com.cn/problem/AT821)

数据较小，暴力+模拟即可。

### 题意：

$ t $ : 保质期

$ n $ : 章鱼烧数量

$ n $ 个整数 $ A_i $ :  第 $ i $ 个章鱼烧的完成时间。

$ m $ : 代表共有 $ m $ 个顾客。

$ m $  个整数 $ B_j $ ：第 $ j $ 个顾客来购买章鱼烧的时间。

#### 首先，高桥做的章鱼烧不够，就没办法卖：

```cpp
if(m>n){cout<<"no"<<endl;return 0;}
```

#### 然后开始比较，判断第 $ j $ 个章鱼烧能不能卖给第 $ i $ 个客户：
>（能卖） 1.  保质期以内，并在顾客来之前做好
>
>（不能卖）0. 过质了（超过保质期）或顾客来之前没做好。

#### 最后如果当前顾客没买到，就输出  “no”  ，停止程序。
#### 否则，直到所有顾客都买到（循环结束），输出  “yes” ，停止程序。

开始比较
```cpp
	int flag=0,now=1;  //flag来确认是否有合格的章鱼烧，now确认下一个人开始寻找的。
	for(int i=1;i<=m;i++){   
        flag=0;   //一开始是没有找到合格的。
        for(int j=now;j<=n;j++){
            if(a[j]>b[i])break;  //因为排过序，所以如果比他大就退出。
            else if(a[j]+t>=b[i]){
                now=j+1;//下一次从j+1开始判断。 
                flag=1; //找到可以卖的。 
                break;//退出。 
            }
        }
        if(!flag){//如果没有可以卖的，直接输出no。 
            cout<<"no"<<endl;
            return 0;
        }
    }
```

最后合在一起就是：

```cpp
 #include<bits/stdc++.h>
using namespace std;
int a[1003],b[1003];
int main(){
	int t,n,m;
	cin>>t>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	cin>>m;
	for(int i=1;i<=m;i++)cin>>b[i];
	if(m>n){cout<<"no"<<endl;return 0;}//章鱼烧不够多啊！！！ 
	int flag=0,now=1;  //flag来确认是否有合格的章鱼烧，now确认下一个人开始寻找的。
	for(int i=1;i<=m;i++){   
        flag=0;   //一开始是没有找到合格的。
        for(int j=now;j<=n;j++){
            if(a[j]>b[i])break;  //因为排过序，所以如果比他大就退出。
            else if(a[j]+t>=b[i]){
                now=j+1;//下一次从j+1开始判断。 
                flag=1; //找到可以买到了。 
                break;//退出。 
            }
        }
        if(flag==0){//如果没有可以卖的，直接输出no。 
            cout<<"no"<<endl;
            return 0;
        }
    }
    cout<<"yes"<<endl;//所有人都分到了，高桥好开心！ 
    return 0;
}
```


---

## 作者：eEfiuys (赞：2)

题目：[AT821](https://www.luogu.com.cn/problem/AT821)
## 输入：
- 第一行一个正整数 $T$，表示保质期，即**章鱼烧开始烧 $T$ 秒后就不能卖了**；
- 第二行一个正整数 $n$，表示章鱼烧数量；
- 第三行 $n$ 个正整数，表示章鱼烧开始做的时间；
- 第四行一个正整数 $m$，表示客人数量；
- 第五行 $m$ 个正整数，表示客人来的时间。
- **数据保证 $O(nm)$ 能过**。

------------

## 思路：
- 输入；
- **从小到大排序**，题目没有说单调不减；
- 从客人 $1$ 枚举到客人 $m$；
	- 从章鱼烧 $1$ 枚举到章鱼烧 $n$；
    - 卖出**时间最早**（因为过期早）的**能卖**的章鱼烧；
    	- 开始烧的时间**早于**客人来的时间；
    	- **没有卖过**；
        - **没有过期**。
    - 对于后面的客人，**从下一个章鱼烧开始枚举**（因为前面的都不能卖了）；
    - 如果没有卖出的，就**输出```no\n```**，**程序结束**。
- 如果对于每位客人都卖出了章鱼烧（枚举完所有客人后**程序还没有结束**），就**输出```yes\n```**。

------------

## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t/*保质期*/,n/*章鱼烧数量*/,m/*客人数量*/;
int a[101]/*章鱼烧开始做的时间*/,b[101]/*客人来的时间*/;
int f=1/*从第几个章鱼烧开始枚举*/；
bool p; //是否卖出。
bool v[101]; //是否卖过。
int main()
{
	cin>>t;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	cin>>m;
	for(int i=1;i<=m;i++)
		cin>>b[i];
    //输入。
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
    //排序。
	for(int i=1;i<=m;i++)
	{
		p=0;
		for(int j=f;j<=n;j++)
			if(!v[j]&&a[j]<=b[i]&&a[j]+t>=b[i]) //能卖出。
			{
				v[j]=1; //改为卖过。
				p=1;
                f=j+1; //从下一个章鱼烧开始。
				break; //只能卖一个。
			}
		if(!p) //没有卖出。
		{
			cout<<"no\n";
			return 0; //程序结束。
		}		
	}
	cout<<"yes\n"; //对于每位客人都卖出了章鱼烧。
	return 0;
}
```

---

## 作者：cjZYZtcl (赞：2)

## AT821 おいしいたこ焼きの売り方 题解
这题可以直接配对。

首先，题目有几个条件：

- 只能卖制作不超过 $T$ 秒的章鱼烧。
- 如果一个客人来了但是没有制作好的章鱼烧，那么那个客人就会走。

所以，我们可以枚举每一个客人，然后给每一个客人配对一个章鱼烧，如果有一个客人配对不上，就输出`no`，否则输出`yes`。

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[105], b[105];
inline int read(){
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
signed main(){
	int t = read(), n = read();
	for(int i = 1; i <= n; i++){
		a[i] = read();
	}
	int m = read();
	for(int j = 1; j <= m; j++){
		b[j] = read();
	}
	int j = 1;
	for(int i = 1; i <= m; i++){
		while((a[j] + t < b[i] || a[j] > b[i]) && j <= n) j++;
		if(j > n){
			puts("no");
			return 0;
		}
		j++;
	}
	puts("yes");
} 
```


---

## 作者：hanyuchen2019 (赞：1)

2021.9.25:修改了一些奇奇怪怪的措辞

首先，我要补充一下这道题的输入格式：

- 第 $1$ 行一个整数 $T$ ($1\le T \le 100$)，表示章鱼烧最多能保存的时间；

- 第 $2$ 行一个整数 $N$ ($1 \le N \le 100$)，表示章鱼烧的数量；

- 第 $3$ 行 $N$ 个整数，第 $i$ 个为 $A_i$($1 \le A_i \le 100,A_1 \le A_2 \le \dots \le A_N$)，表示第 $i$ 个章鱼烧熟的时间；

- 第 $4$ 行一个整数 $M$ ($1 \le M \le 100$)，表示客人的数量；

- 第 $5$ 行 $M$ 个整数，第 $i$ 个为 $B_i$($1 \le B_i \le 100,B_1 \le B_2 \le \dots \le B_M$)，表示第 $i$ 个客人到来的时间；


贪心水题，我的思路是对于每一个到来的顾客，挑选现在已经烧好未“过期”的最先烧好的章鱼烧，可保证结果最优。

```cpp
#include<iostream>
using namespace std;
int a[103],b[103];
int main()
{
	int T,n,m;
	cin>>T;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	cin>>m;
	for(int i=1;i<=m;i++)
		cin>>b[i];
	int f=1;
   //表示第f个章鱼烧之前的都“过期”或卖掉了，因为题目中保证从小到大，如果一个章鱼烧过期，前面的一定过期。
	for(int i=1;i<=m;i++)
	{
		bool c=false;//标志变量，表示是否买到章鱼烧
		for(;f<=n;f++)
		{
			if(a[f]+T>=b[i]&&a[f]<=b[i])//没有过期并且已经烧好
			{
				c=true;
				f++;//这个章鱼烧买走了
				break;//退出，找下一个顾客
			}
		}
		if(c==false)
		{
			cout<<"no"<<endl;
			return 0;
		}
	}
	cout<<"yes"<<endl;
	return 0;
}
```

---

## 作者：Fire_Raku (赞：0)

### 题目分析：

这是一道贪心题：要把所有的章鱼烧都卖出，那么我们就试试模拟卖章鱼烧的过程。首先，我们输入完之后，我们就枚举顾客，里面枚举所有的章鱼烧，如果所有的章鱼烧里面都没有能够与这个顾客能买的章鱼烧的话，那就直接输出 `no`，结束代码；如果在枚举完所有顾客后都没有停止程序的话，就说明所有人都买到了章鱼烧。

章鱼烧是否符合条件：
1. 是否在顾客来之前开始烧
2. 有没有超过保质期

### Code：

```cpp
#include<bits/stdc++.h>
using namespace std ;
int t , n , m , e = 1 , a[1000010] , b[1000010] ; 
int main(){
	cin >> t >> n ; 
	for(int i = 1 ; i <= n ; i++) cin >> a[i] ; 
	cin >> m ; 
	for(int i = 1 ; i <= m ; i++) cin >> b[i] ; 
	for(int i = 1 ; i <= m ; i++){
		bool flg = 0 ; //初始化
		for(int j = e ; j <= n ; j++){
			if(a[j] + t >= b[i] && a[j] <= b[i]){ //如果这个章鱼烧在顾客来之前烧的且没有过保质期
				e = j + 1 ; //因为这个顾客到这个章鱼烧才买了，所以后面的人买的章鱼烧肯定比这个顾客还晚，直接从下一个枚举
				flg = 1 ; 
				break ; 
			}
		} 
		if(!flg){ //如果没有合适的章鱼烧
			cout << "no" << endl ; 
			return 0 ; 
		}
	}
	cout << "yes" << endl ; //都买到了合适的章鱼烧
	return 0 ; 
}
```

---

## 作者：MrCR7 (赞：0)

## 简述题意
高桥君正在卖章鱼烧，你做出的章鱼烧不能超过保质期，否则不能卖出。

输入的第一行一个整数 $t$，代表每个章鱼烧的保质期，即当每个章鱼烧制作完成到卖出的时间超过 $t$，则不能卖出。

输入的第二行一个整数 $n$，代表共有 $n$ 个章鱼烧。

输入的第三行 $n$ 个整数 $a_i$，代表第 $i$ 个章鱼烧的完成时间。

输入的第四行一个整数 $m$，代表共有 $m$ 个顾客。

输入的第五行 $m$ 个整数 $b_j$，代表第 $j$ 个顾客来购买章鱼烧的时间。

## 算法思路
这道题模拟 $+$ 暴力就可以了。

毕竟 $a,b \leq 100$。

我们需要这样判断。

如果输入的 $n < m$，则直接输出 $\texttt{no}$。

接下来从小到大排序。

然后从第一个客户开始枚举是否可以购买章鱼烧，判断第 $j$ 个章鱼烧在卖给第 $i$ 个客户时是否在保质期内，并在顾客来之前制作完成，如果不满足，开始下一轮。

如果都没有可以卖的，直接输出 $\texttt{no}$。

如果每个客户都可以买到章鱼烧，则输出 $\texttt{yes}$。

## Ac Code
```cpp
#include<cstdio>
#include<algorithm>
int a[105],b[105];//如题意。 
int main(){
	int t,n,m;
	scanf("%d\n%d",&t,&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);//读入。 
	scanf("%d",&m);
	for(int i=1;i<=m;i++) scanf("%d",&b[i]);//读入。 
	if(m>n){//第一次判断，如思路描述。 
		printf("no\n");
		return 0;
	}
	std::sort(a+1,a+n+1);
	std::sort(b+1,b+m+1);//从小到大排序。 
	int now=1;//这个变量的是用来储存现在判断到哪个章鱼烧的。 
	bool flag=false; 
	for(int i=1;i<=m;i++){
		flag=false;//先把它变成FALSE。 
		for(int j=now;j<=n;j++){
			if(a[j]+t>=b[i]&&a[j]<=b[i]){//判断第j个章鱼烧在卖给第i个客户时是否在保质期内，并在顾客来之前制作完成。 
				now=j+1;//下一次从j+1开始判断。 
				flag=true;//又可以卖的，就变为TRUE。 
				break;//退出。 
			}
		}
		if(!flag){//如果没有可以卖的，直接输出no。 
			printf("no\n");
			return 0;
		}
	}
	printf("yes\n");
	return 0;
}
```
完结撒花qwq~

---

## 作者：COsm0s (赞：0)

这里要注意题目条件：

 只能卖制作不超过 $T$ 秒的章鱼烧。
 
 如果一个客人来了但是没有制作好的章鱼烧，那么那个客人就会走。
 

------------

考虑贪心，因为题目有求最优解的意思。

策略：

由于数据必定有序（客人来的顺序和章鱼烧的完成顺序是依次递增的），那我们可以将一个客人与一个章鱼烧分为一组，共分为 $n$ 组。

如果客人与章鱼烧不能分组了，（即有客户不能吃到任意一个章鱼烧）则本数据无解，输出 no 。如果所有客户都成功配对了，则本数据有解，输出 yes 。



```cpp
for(int i=1; i<=m; ++i) {//枚举人
	bool p=0;
	for(int j=y+1; j<=n; ++j) { //枚举章鱼烧
		if(a[j]<=b[i]&&a[j]+t>=b[i]) { //满足配对条件
			p=1;
			y=j;//判重，下一次从当前项的下一个开始枚举 
			break;
		}
	}
	if(!p) {
		cout<<"no"<<endl;    //无法配对，输出no
		return 0;
	}
}
```

如上述伪代码
开始比较，判断第 $i$ 个客户能不能吃第 $j$ 个章鱼烧：

  1、 保质期以内，并在顾客来之前做好（买了）

  2、 保质期以外，或顾客来之前没做好（开始尝试下一个章鱼烧）

最后如果当前顾客没买到，就输出 “no” ，直接停止程序。
否则，输出 “yes” ，停止程序。

下面奉上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[1000],b[1000];
inline int read() {//快读 
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)) {
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)) {
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x) {//快输 
	if(x < 0) {
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
signed main() {
	int t=read(), n=read();
	for(int i=1; i<=n; i++) 
		a[i]=read();
	int m = read();
	for(int j=1; j<=m; j++) 
		b[j]=read();
		//输入 
	for(int i=1; i<=m; ++i) {
		bool p=0;
		for(int j=y+1; j<=n; ++j) { //枚举章鱼烧
			if(a[j]<=b[i]&&a[j]+t>=b[i]) { //满足配对条件
				p=1;
				y=j;//判重，下一次从当前项的下一个开始枚举
				break;
			}
		}
		if(!p) {
			cout<<"no"<<endl;    //无法配对，输出no
			return 0;
		}
	}
	cout<<"yes";//可以配对 
	return 0; 
} 
```


------------

时间复杂度 $O(nm)$。

---

## 作者：Otue (赞：0)

题目已经告诉我们 $a$ 数组和 $b$ 数组已经有序，所以不用排序。

客人买的章鱼烧必须是之前做好且没有过期的。

高桥为了维持生意卖的章鱼烧优先先卖 **最早做好且没有过期** 的章鱼烧。

注意卖过的章鱼烧不要再买，然后代码实现很简单。

```c++
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, t, m, a[N], b[N];
int last = 1;

int main() {
    cin >> t >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> m;
    for (int i = 1; i <= m; i++) cin >> b[i];
    if (m > n) {   //章鱼烧不够了
        puts("no");
        return 0;
    }
    for (int i = 1; i <= m; i++) {
        bool flag = 0;
        for (int j = last; j <= n; j++) {
            if (a[j] <= b[i] && a[j] + t >= b[i]) {
                flag = 1;
                last = j + 1;
                break;
            }
        }
        if (flag == 0) {
            puts("no");
            return 0;
        }
    }
    puts("yes");
}
```

---

