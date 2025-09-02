# Mike and Fun

## 题目描述

Mike and some bears are playing a game just for fun. Mike is the judge. All bears except Mike are standing in an $ n×m $ grid, there's exactly one bear in each cell. We denote the bear standing in column number $ j $ of row number $ i $ by $ (i,j) $ . Mike's hands are on his ears (since he's the judge) and each bear standing in the grid has hands either on his mouth or his eyes.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF548B/7fc4231ff2f142e0d53dc7e0b0a98c037c896437.png)
 
 They play for $ q $ rounds. In each round, Mike chooses a bear $ (i,j) $ and tells him to change his state i. e. if his hands are on his mouth, then he'll put his hands on his eyes or he'll put his hands on his mouth otherwise. After that, Mike wants to know the score of the bears.

Score of the bears is the maximum over all rows of number of consecutive bears with hands on their eyes in that row.

Since bears are lazy, Mike asked you for help. For each round, tell him the score of these bears after changing the state of a bear selected in that round.

## 样例 #1

### 输入

```
5 4 5
0 1 1 0
1 0 0 1
0 1 1 0
1 0 0 1
0 0 0 0
1 1
1 4
1 1
4 2
4 3
```

### 输出

```
3
4
3
3
4
```

# 题解

## 作者：BearBig (赞：2)

### 题目简述
首先给你两个整数 $w$，$h$，$q$。    
接下来给你一个 $w \times h$ 的
`bool` 类型的方阵，表述一个数组。    
接下来的 $q$ 行，每行两个整数 $ow$，$oh$，表示将 $ow$ 行 $oh$ 列的元素转换成相反的数值。    
要求输出每一系操作以后，连续的一的最多的个数 。
### 思路分析
首先声明变量，没有问题。
```python
fz=[]
w,h,q=input().split(' ')
w,h,q=int(w),int(h),int(q)
```
接下来是输入，也不是问题，使用
`while` 循环。
```python
while w:
		w-=1
		h1=input().split(' ')
        for i in range(len(h1)):
        	h1[i]=int(h1[i])
        fz.append(h1)
```
接下来定义函数，表示寻找最多的 1 的个数。这个函数的原理非常简单，就是不断找最多的连续的 1 的个数，发现 0 就标记当前
```python
def biggest(r):
		mx=0
		for i in r:
        cntin=0
        lcmx=0
        for j in i:
        	if j==True:
            cntin+=1
          elif j==False:
          		if cntin>lcmx:
          `	 		lcmx=cntin
            cntin=0
         if lcmx>mx:
         	mx=lcmx
 		return mx
```
最后进行输入的是每一次操作。
```python
while q:
		q-=1
        que=input().split(' ')
        for i in range(len(que)):
        	que[i]=int(que[i])
        fx[que[0]][que[1]]=1-fx[que[0]][que[1]]# 将列表指定项目换过来
        print(biggest(fx))
        
```
### 代码分享
根据以上步骤，无注释代码如下。
```python
def biggest(r):
		mx=0
		for i in r:
        cntin=0
        lcmx=0
        for j in i:
        	if j==True:
            cntin+=1
          elif j==False:
          		if cntin>lcmx:
          `	 		lcmx=cntin
            cntin=0
         if lcmx>mx:
         	mx=lcmx
 		return mx
fz=[]
w,h,q=input().split(' ')
w,h,q=int(w),int(h),int(q)
while w:
		w-=1
		h1=input().split(' ')
        for i in range(len(h1)):
        	h1[i]=int(h1[i])
        fz.append(h1)
while q:
		q-=1
        que=input().split(' ')
        for i in range(len(que)):
        	que[i]=int(que[i])
        fx[que[0]][que[1]]=1-fx[que[0]][que[1]]# 将列表指定项目换过来
        print(biggest(fx))
```
**珍爱生命，远离抄袭！**

---

## 作者：Luo_gu_ykc (赞：1)

## 题目大意
给定一个 01 矩阵， 给定 $q$ 次修改， 每次将一个矩阵上的点取反， 修改后立即求出求出连续的 1 最多的一行中连续的 1 的个数。
## 思路
模拟即可， ~~这不就一道大水题~~ ；

话不多说， 上代码！！！
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, q, cnt[5005];
bool a[505][505];
int main(){
	cin >> n >> m >> q;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			cin >> a[i][j];
		}
	}
	for(int lll = 1; lll <= q; lll++){
		int x, y, maxi = 0;
		cin >> x >> y;
		a[x][y] = !a[x][y]; // 取反
		for(int i = 1; i <= n; i++){
			int sum = 0;
			for(int j = 1; j <= m; j++){
				if(a[i][j] == 1){ // 记住是连续的 1
					sum++;
				} else{
					sum = 0;
				}
				maxi = max(maxi, sum);
			}
		}
		cnt[lll] = maxi; // 用数组记录， 最后输出 （个人风格）
	}
	for(int i = 1; i <= q; i++){
		cout << cnt[i] << "\n";
	}
	return 0;
}
```

---

## 作者：reclusive (赞：1)

# 题目大意：

现在有一个长度为 $n$，宽度为 $m$ 的矩阵，

矩阵里是 $0$ 和 $1$ 两种数字，然后有 $q$ 次访问，

每一次访问可以将原来是 $0$ 的位置变成 $1$，或者将原来是 $1$ 的位置变成 $0$。

最后让你求每一行里连续 $1$ 最多的个数。

# 解题思路：

这道题我第一时间想到的就是暴力求解，

于是就有了第一篇代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[501][501];
int main()
{
	int n,m,q;
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	for(int i=1;i<=q;i++)
	{
		int x,y,s,maxn;
		scanf("%d%d",&x,&y);
		if(a[x][y]==1)
		{
			a[x][y]=0;
		}
		else
		{
			a[x][y]=1;
		}
		maxn=0;
		for(int j=1;j<=n;j++)
		{
			s=0;
			for(int k=1;k<=m;k++)
			{
				s+=a[j][k];
			}
			if(s>maxn)
			{
				maxn=s;
			}
		}
		printf("%d\n",maxn);
	}
	return 0;
}
```
但是我错了。

我看了一眼 $n$ $m$ $q$ 的范围，暴力的话要算 $1250000000$ 次，肯定会慢。

所以暴力肯定是不行的。

所以我有了第二个想法。

就是说我们每一次访问只会改变当前行的情况，

对其他行并不会造成实质性影响。

所以思路就明确了。

我们访问前先将每一行连续的 1 的个数算出来，

访问时将那一行重新算一遍，

然后最后有一个叫 $maxn$ 的变量，

用 $maxn$ 和每一行的个数作比较，得出结果。

```cpp
maxn=0;//每一行连续1的最大值
for(int j=1;j<=n;j++)//开始比较
{
	if(b[j]>maxn)//比前面的大就重新赋值
	{
		maxn=b[j];
	}
}
printf("%d\n",maxn);///输出
```


---

## 作者：开始新的记忆 (赞：1)

大意：

在一个n*m的矩阵上，每个方格中有一只熊，这只熊要么是捂着眼睛的（用1表示），要么是捂着嘴巴的（用0表示）。共q组询问，每组询问有两个数x，y，你现在想知道在修改了x，y这只熊的状态（1->0,0->1）后，整个矩阵中最多有多少只在同一行的连续的熊是捂着眼睛的

纯暴力……


```
#include<bits/stdc++.h>
using namespace std;
int n,m,q,ans[510][510],maxn[510];
bool a[510][510];
int main()
{   cin>>n>>m>>q;
    for(int i=1;i<=n;++i)
    	for(int j=1;j<=m;++j)
    	{
    		cin>>a[i][j];
    		ans[i][j]=a[i][j]+ans[i][j-1]*a[i][j];
    		maxn[i]=max(maxn[i],ans[i][j]);
		}
	while(q--)
	{
		int x,y;
		cin>>x>>y;
		a[x][y]=!a[x][y];
		maxn[x]=0;
		for(int i=1;i<=m;++i)
		{
    		ans[x][i]=a[x][i]+ans[x][i-1]*a[x][i];
    		maxn[x]=max(maxn[x],ans[x][i]);
		}
		int maxx=0;
		for(int i=1;i<=n;++i)
		    maxx=max(maxx,maxn[i]);
		cout<<maxx<<endl;
	}
    return 0;
}
```


---

## 作者：_Spectator_ (赞：0)


[可能更好的食用体验](/blog/523641/CF548B) $|$ 
[题目传送门](/problem/CF548B) $|$ 
[我的其他题解](/blog/523641/#type=题解)

虽然是一道模拟题，在做的时候还是有许多需要注意的地方。没什么好讲的，自己看代码吧。

------------

${\large\color{#00CD00}\text{完整代码}}$

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,q,x,y;
bool a[505][505];//01矩阵，用bool存最合适不过了。
int main()　
{　
	cin>>n>>m>>q;　
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	while(q--)　
	{　
		cin>>x>>y;　
		a[x][y]=!a[x][y];//取反
		int len=0,ma=0;//注意这里定义不能用long long！否则会超时
		for(int i=1;i<=n;i++,len=0)
			for(int j=1;j<=m;j++)
			{　
				if(a[i][j])len++;//如果是1，增加len
				else len=0;　
				ma=max(ma,len);
			}　
		cout<<ma<<endl;
	}　
	return 0;
}　
```

[关于第 $15$ 行](/discuss/414373)

**[${\color{Black}\textbf{xt\_\_}}$](/user/523641) 温馨提示：**


${\large\color{White}\text\colorbox{#AD8800}{题解千万条，理解第一条。直接粘题解，棕名两行泪。}} $

---

## 作者：LYqwq (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF548B)

# 题目大意

有一个 $n \times m$ 的 $01$ 矩阵 $a$。要进行 $q$ 次操作，每次操作将 $a_{x,y}$ 取反，并询问连续的 $1$ 最多的一行中连续的 $1$ 的个数。

$1 \le n,m \le 500,1 \le q \le 5000,1 \le x \le n,1 \le y \le m$。

# 思路

可以先考虑暴力。

完全按照题目中说的做，遍历每一行，在每行中找到连续的 $1$ 最多的个数，总时间复杂度 $\mathcal{O}(nmq)$。

然而...[TLE on #15](https://www.luogu.com.cn/record/70311399)。

不知道那几篇暴力题解咋过的，可能是数据又加强了吧。

然后就要考虑更快的办法了。

很容易发现，每次操作影响的只是一行，只需花 $\mathcal{O}(m)$ 的时间将这一行重新统计一遍就行了。

可以在输入时先算出每行最多的连续个数，存入数组。在询问时 $\mathcal{O}(n)$ 的时间遍历一遍数组求出最大值。

那么总时间复杂度就是 $\mathcal{O}(nm+(n+m)q)$。

~~嘿嘿，这下你卡不到我了吧...~~

# 代码

## 暴力(TLE)

```cpp
#include <iostream>
using namespace std;
const int N=5e2+5;
int n,m,q,x,y,sum,ans;
bool a[N][N];

int main(){
    cin >> n >> m >> q;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            cin >> a[i][j];
        }
    }
    while(q--){
        cin >> x >> y;
        a[x][y]=!a[x][y]; // 取反
        for(int i=1; i<=n; i++,sum=0){ // 别忘了把 sum 置 0
            for(int j=1; j<=m; j++){
                if(a[i][j]) sum++; // 还是连续的，则加一
                else sum=0; // 碰到一个 0，连续就断了
                ans=max(ans,sum); // 每次都更新一下答案
            }
        }
        cout << ans << endl;
        ans=0; // 初始化
    }
    return 0;
}
```

## 预处理

```cpp
#include <iostream>
using namespace std;
const int N=5e2+5;
int n,m,q,x,y,sum,ans;
bool a[N][N];
int mp[N];

int main(){
    cin >> n >> m >> q;
    for(int i=1; i<=n; i++,sum=0){ // 别忘了把 sum 置 0
        for(int j=1; j<=m; j++){
            cin >> a[i][j];
            if(a[i][j]) sum++; // 还是连续的，则加一
            else sum=0; // 碰到一个 0，连续就断了
            mp[i]=max(mp[i],sum); // 每次都更新一下答案
        }
    }
    while(q--){
        cin >> x >> y;
        a[x][y]=!a[x][y]; // 取反
        mp[x]=0; // 这句不能忘
        for(int i=1; i<=m; i++){
            if(a[x][i]) sum++;
            else sum=0;
            mp[x]=max(mp[x],sum);
        }
        for(int i=1; i<=n; i++){
            ans=max(ans,mp[i]); // 找最大值
        }
        cout << ans << endl;
        sum=0,ans=0; // 初始化
    }
    return 0;
}
```



---

## 作者：lelml (赞：0)

很简单的一道模拟题QwQ

### 思路

按照题意模拟。每一次改一个点，用一个数组记录每一行 1 的数量，擂台法比较得出最大值，新的一次修改开始时别忘了清空数组哦~

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q;
bool a[501][501];
int main(){
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>a[i][j];
	for(int k=1;k<=q;k++){
		int x,y,maxi=0;
		cin>>x>>y;
		a[x][y]=!a[x][y];
		for(int l=1;l<=n;l++){
			int sum=0;
			for(int o=1;o<=m;o++){
				if(a[l][o]==1) sum++;
				else {sum=0;maxi=max(maxi,sum);}
			}
		}
		cout<<maxi<<endl;
	}
	return 0;
}

```

---

## 作者：linnaeuss (赞：0)

[AC 记录](https://www.luogu.com.cn/record/56860349)

### 题意 ：
* 有一个  $ n\times m  $  的  $ 01 $  矩阵 。  
* $ q $ 次修改，每次将一个点上的数反转 （  0  变成 1 ，  1  变成  0 ） 。
* 每次修改后一次询问 ，求连续的 1 最多的一行中连续的 1 的个数 。
* $ n,m\leqslant 500 $  ,  $ q\leqslant 5000 $ 




### 思路 ：
~~众所周知，入门题不会考太难的算法~~ 。   
这题直接模拟即可。


 具体见代码 。




### AC 代码 ：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q;
int a[505][505];
int sum[505];

void SUM(int i){
	int maxn=0;                          //目前有几个连续的 1
	sum[i]=0;
	for(int j=1;j<=m;j++){
		if(a[i][j]==1){
			maxn++;                      //如果是一，连续数量 ++
		}else{
			sum[i]=max(sum[i],maxn);     //否则更新最大值
			maxn=0;
		}
	}
	sum[i]=max(sum[i],maxn);
	//别忘了还要更新一遍
	//如果这行最后一个是 1 ，那么循环结束后 now 还没更新到 maxn 里
}

void work(){
	int maxn=0;                      //每行最大值的最大值
	for(int i=1;i<=n;i++){
		maxn=max(maxn,sum[i]);       //更新最大值
	}
	printf("%d\n",maxn);
}

int main(){
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++){
    	for(int j=1;j<=m;j++){
    		scanf("%d",&a[i][j]);    //读入
		}
	}
	for(int i=1;i<=n;i++){
		SUM(i);                      //预处理 sum 数组
	}
	while(q--){
		int x,y;
		scanf("%d%d",&x,&y);
		if(a[x][y]==1){              //修改
			a[x][y]=0;
		}else{
			a[x][y]=1;
		}
		SUM(x);                      //重新算出第 x 行的最大值
		work();                      //找出最大值最大的一行
	}
    return 0;
}
```


---

## 作者：thomas_zjl (赞：0)

一个细节很多的模拟。

### 题目大意。

- 给我们一个 $01$ 矩阵，有 $q$ 次修改，把这个点的数翻转。	
- 再输出连续的 1 最多的一行中连续的 1 的个数。

### 基本思路。

1. 我先求一下输出连续的 1 最多的一行中连续的 1 的个数，把**每一行**最多连续的 1 的个数保存，因为后面修改时只改变 1 行中的 1 个点，不会改变其他行的数量。

1. 在每一次询问中 ， 只用再算一次改变的那一个行就可以了，在对每一行最多连续的 1 的个数进行比较出最大值。

下面是完成第一步的代码。
```cpp
//cnt 代表当前连续 1 的个数的序列长度。
//num 代表这一行最大连续 1 的序列的长度。
//flag 代表是否有 1。
//a[i][j] 代表输入的矩阵。
//ans[i] 代表第 i 行最大连续 1 的序列的长度。
int cnt,num;
bool flag;
for(int i=1;i<=n;i++){
	cnt=num=flag=0;//初始化。
	for(int j=1;j<=m;j++){
		if(a[i][j]==1)//如果这里有一个 1 。
			flag=1;//flag为true。
		if(a[i][j]==a[i][j-1]&&a[i][j]==1)//如果 1 是连续的。
			cnt++;//cnt+1。
		else{//如果有一个 0 。
			if(cnt>0)//当 cnt 不为零时进行判断。
				num=max(cnt+1,num);//cnt 要加 1 是因为没有把第一个 1 算进去。
			cnt=0;//重置cnt。
		}
	}
	if(cnt>0)//最后还要判断一下，因为全部是 1 会输出 0 。
		num=max(cnt+1,num);
	if(flag)//如果这里有 1 。
		ans[i]=max(1,num);//那么 ans[i] 一定比 1 大。
	else//如果没有。
		ans[i]=0;//ans[i] 为 0 。
} 
```

下面是完成第二步的代码。
```cpp
int x,y;
while(q--){
	cin>>x>>y;//输入。
	if(a[x][y]==1)
		a[x][y]=0;
	else
		a[x][y]=1;
	//这里是来进行数字的翻转。
	cnt=num=flag=0;
	for(int i=1;i<=m;i++){//只有一层循环，来计算这一行连续 1 的序列的长度。
		if(a[x][i]==1)
			flag=1;
		if(a[x][i]==a[x][i-1]&&a[x][i]==1)
			cnt++;
		else{
			if(cnt>0)
				num=max(cnt+1,num);
			cnt=0;
		}
	}
	if(cnt>0)
		num=max(cnt+1,num);
	int sum=0;
	if(flag)
		ans[x]=max(1,num);
	else
		ans[x]=0;
   //上面的几行代码就是来计算这一行连续 1 的序列的最大长度的，与上一个代码没什么区别。
	for(int i=1;i<=n;i++)
		sum=max(sum,ans[i]);//这里是计算最大的连续 1 的序列的最大长度的。
	cout<<sum<<endl;//输出，换行。
}
```


```cpp
#include<bits/stdc++.h>
using namespace std;
int a[501][501];
int ans[501];
int main(){
	ios::sync_with_stdio(false);
	int n,m,q;
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	int cnt,num;
	bool flag;
	for(int i=1;i<=n;i++){
		cnt=num=flag=0;
		for(int j=1;j<=m;j++){
			if(a[i][j]==1)
				flag=1;
			if(a[i][j]==a[i][j-1]&&a[i][j]==1)
				cnt++;
			else{
				if(cnt>0)
					num=max(cnt+1,num);
				cnt=0;
			}
		}
		if(cnt>0)
			num=max(cnt+1,num);
		if(flag)
			ans[i]=max(1,num);
		else
			ans[i]=0;
	} 
   //上面是对每一行最多连续的 1 的个数进行计算。 
	int x,y;
	while(q--){
		cin>>x>>y;
		if(a[x][y]==1)
			a[x][y]=0;
		else
			a[x][y]=1;
		cnt=num=flag=0;
		for(int i=1;i<=m;i++){
			if(a[x][i]==1)
				flag=1;
			if(a[x][i]==a[x][i-1]&&a[x][i]==1)
				cnt++;
			else{
				if(cnt>0)
					num=max(cnt+1,num);
				cnt=0;
			}
		}
		if(cnt>0)
			num=max(cnt+1,num);
		int sum=0;
		if(flag)
			ans[x]=max(1,num);
		else
			ans[x]=0;
		for(int i=1;i<=n;i++)
			sum=max(sum,ans[i]);
		cout<<sum<<endl;
	}
   //上面是对每一个询问并只针对那一行进行计算，在进行输出答案。
}
```


---

