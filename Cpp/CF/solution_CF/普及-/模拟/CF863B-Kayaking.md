# Kayaking

## 题目描述

Vadim真的很喜欢旅行。（所以）当他听说在他的小镇附近有一个皮划艇大赛的时候，是十分激动的，所以，他参加了这场皮划艇的聚会。

现在聚会已经准备好开始了他们的皮划艇之旅了，但首先，他们需要选择皮划艇。这有 $2n$ 个人（包括Vadim），并且他们有$n-1$ 个双人皮划艇（当然，每个可以坐两个人）和$2$ 个单人皮划艇。第$i$ 个人的体重是$w_i$ ，并且体重在皮划艇中是一件重要的事——如果坐在同一个双人皮划艇上的两人的体重相差太多，皮划艇就会倾覆。当然，人们想要分配他们的座位来最小化使皮划艇倾覆的可能性。

事实上，单人皮划艇的不稳定性总是$0$ ，并且双人皮划艇的不稳定性为在皮划艇上两人体重的差的绝对值。在整场旅行中的不稳定值就是所有皮划艇不稳定值的和。

帮助这个聚会找出最小的总不稳定值！

## 样例 #1

### 输入

```
2
1 2 3 4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
1 3 4 6 3 4 100 200
```

### 输出

```
5
```

# 题解

## 作者：TLMPEX (赞：3)

思路：我们可以枚举哪两个单独坐的人，然后用一个函数再枚举剩下坐两个一起坐的人，不断的加上重量差，最后返回最终重量差，在所有返回的结果中取最小的，最后输出。
```c
#include<iostream>
#include<algorithm>
using namespace std;
int k[101],n;
int sol(int x,int y){
    int i,s=0,c=0,a[2];//c代表这艘双人小艇已坐了多少人，a表示这艘双人小艇分别坐了的人重量
    for(i=1;i<=n*2;i++){
        if(i==x||i==y)continue;//如果是哪两个单独坐的人，就跳过。
        a[c++]=k[i];//否则把第i个人的重量放到a数组里
        if(c==2){//如果人满了，就把两人重量的差加到变量s里，并把c清0
            s+=a[1]-a[0];
            c=0;
        }
    }
    return s;
}
int main(){
	int i,j,p=100001;
	cin>>n;
	for(i=1;i<=n*2;i++)
		cin>>k[i];
	sort(k+1,k+2*n+1);
	for(i=1;i<n*2;i++)//枚举单独坐的人
		for(j=i+1;j<=n*2;j++)
			p=min(sol(i,j),p);//更新p
	cout<<p;
}
```


---

## 作者：loushujia (赞：1)

# [CF863B](https://www.luogu.com.cn/problem/CF863B)题解
### 思路
先枚举出两个去坐单人船的人，然后把剩下的人排序，求出他们的不稳定值的总和，比较出最小的一个，输出。
### 代码
```cpp
#include<bits/stdc++.h>
#include<algorithm>
using namespace std;
int n, a[105], sum, minm = 1000;//minm 是最小值。
int main() {
	scanf("%d", &n);//输入。
	for (int i = 1; i <= n * 2; i++)
		scanf("%d", &a[i]);//输入每个人的体重。
	sort(a + 1, a + 1 + n);
	for (int i = 1; i < n * 2; i++) {//枚举。
		for (int j = i + 1; j <= n * 2; j++) {
			for (int k = 1; k < n * 2; k++) {
				int c = k + 1;
				if (k == i || k == j) continue;//跳过去坐单人船的两人。
				while (c == i || c == j) c++;//如果第 k+1 个人去坐单人船了，找到他后面不坐单人船的人。
				sum += fabs(a[c] - a[k]);//不稳定值。
				k = c;
			}
			minm = min(sum, minm);//最小值。
			sum = 0;//清空。
		}
	}
	printf("%d", minm);//输出。
	return 0;//华丽的结束。
}
```


---

## 作者：_shine_ (赞：1)

## 题目大意
现在有 $2 \times n$ 个人，第 $i$ 个人重量为 $w_i$，有 $n$ 个皮划艇，其中，有 $n-2$ 个双人皮划艇，$2$ 个单人皮划艇，但是，双人皮划艇的两个人如果体重相差太大就会沉没，现在问你总的最小不稳定值。
## 思路
可以使用暴力的思想，不难发现，对于每一个使用双人皮划艇的人，每艘的最小稳定值肯定是 $\min_{w_y-w_x}$。因此，考虑每次对那 $2$ 个单人皮划艇进行暴力枚举，从那 $n\times2$ 个人中枚举每两个人 $i,j\left(i\ne j\right)$，每次枚举 $i,j$ 时循环出此时没艘皮划艇的稳定值即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e3+10;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')w=-1;ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        s=s*10+ch-'0';
        ch=getchar();
    }
    return s*w;
}
inline void write(int x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9)write(x/10);
    putchar(x % 10 + '0');
}
int n;
vector<int>a;
int ans=INT_MAX;
void get_ans(int x,int y){//计算每次枚举的稳定值。
	int num=0;
	vector<int>p(2,0);
	p.clear();
	for(int i=0;i<n*2;++i){
		if(i!=x && i!=y){
			p.push_back(a[i]);
			if(p.size()>=2){
				num+=p[1]-p[0];
				p.clear();
			}
		}
	}
	ans=min(ans,num);
}
signed main(){
	n=read();
	for(int i=1;i<=n*2;++i){
		int x=read();
		a.push_back(x);
	}
	sort(a.begin(),a.end());
	for(int i=0;i<n*2;++i){
		for(int j=i+1;j<n*2;++j){//一个小小的优化，这样可以避免j从1开始时会重复的现象。
			get_ans(i,j);
		}
	}
	write(ans);
	return 0;
}

```


---

## 作者：_zxh110408 (赞：1)

## 思路
这个这题我们可以暴力枚举所有的情况。

现枚举出两个人，让他们去坐单人船。然后将剩下人的体重从小到大排序，按照排序的结果两两配对（跳过去做单人皮划艇的人），让他们去坐双人皮划艇，用这种方法总不稳定值尽可能的小，并求出总不稳定值，不断比较这个不稳求出，最小的一个，输出。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,k;vector<int>a;
	cin>>n;
	n*=2;int ans=99999999;
	for (int i=0;i<n;i++){
		cin>>k;a.push_back(k);
	}
	for (int i=0;i<n;i++){
		for (int j=i+1;j<n;j++){
			vector <int> V;
			for (int jj=0;jj<n;jj++){
				if (jj!=i and jj!=j){
					V.push_back(a[jj]);
				}
			}
			int mm=0;sort(V.begin(),V.end());
			for (int jj=0;jj<V.size();jj+=2){
				mm+=V[jj+1]-V[jj];
			}
			ans=min(ans,mm);
		}
	}
	cout<<ans;
	return 0;
}


```

---

## 作者：YUYGFGG (赞：1)

思路：因为只有两条单人皮艇，可以排除坐单人皮艇的两个人，剩下的数排序并求出相邻两数差值的和$sum$（最小的稳定性一定是排序后两两相邻数的差值之和），求出做小的$sum$

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1001];
int main(){
    int n,m,we;
    m=10000;
    int s=0;
    cin>>n;
    for(int i=0;i<2*n;i++)
        cin>>a[i];
    sort(a,a+2*n);
    for(int i=0;i<2*n;i++)
        for(int j=i+1;j<2*n;j++){
            we=s=0;
            for(int l=0;l<2*n;l++)
                if(l^i&&l^j){
                    if(we){
                        s+=a[l]-we;
                        we=0;
                    }
                    else
                        we=a[l];                        
                }
            if(m>s)
                m=s;
        }
    cout<<m<<endl;
    return 0;
}

```


---

## 作者：Mingci (赞：0)

# CF863B Kayaking
## 题目大意:
有 $2n$ 人，$n-1$ 艘双人艇，$2$ 艘单人艇，定义一艘双人艇的不稳定值为坐在艇上的两个人之间的体重差的绝对值，特殊地，单人艇不稳定值为零。求一个方案使得不稳定值最小，输出最小的不稳定值。
## 题目分析：
首先需要把所有 $2n$ 个人从小到大排序，使得我们枚举的时候能自然而然的选出每个双人艇坐的人选。但是两个单人艇又该如何处理呢？考虑枚举。由于数据范围不大，我们可以在所有人之中枚举坐单人艇的两个人，并求出当这两个人坐单人艇时的不稳定值，将所有不稳定值加起来，所有可能中最小的不稳定值和就是答案。
## 代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,w[5005],sum,/*每种可能的不稳定值*/cnt,minn=0x3f3f3f3f;//把minn定义为无限大
int work(int one,int two){
	sum = 0,cnt = 0;//记得每枚举一种可能都要初始化
	int a[3]={0};//用来存放一艘二人艇上的两个人
	for(int i = 1;i <= (n<<1);i++){//枚举二人艇上坐的人
		if(i!=one&&i!=two)a[cnt++]=w[i];//如果没有坐在单人艇上就加入到里面
		else continue;//否则跳过这个人
		if(cnt==2)sum+=abs(a[1]-a[0]),cnt=0;//当一艘二人艇满了，加上不稳定值换成下一艘二人艇装
	}
	return sum;//返回答案
}
signed main(){
	cin >> n;
	for(int i = 1;i <= (n<<1);i++)cin >> w[i];
	sort(w+1,w+1+2*n);//先排序
	for(int i = 1;i <= (n<<1)-1;i++)//枚举2*n-1个人
		for(int j = i+1;j <= (n<<1);j++)//第二个坐单人艇的人
			minn=min(minn,work(i,j));//所有可能中取最小值
	cout << minn << endl;//输出
	return 0;//华丽结束~
}

```


---

## 作者：Berd__ (赞：0)

### 题目大意

有 $2n$ 个人，第 $i$ 个人重量为 $w_i$，有 $n + 1$ 个皮划艇，其中，有 $n-1$ 个双人皮划艇，$2$ 个单人皮划艇，但是，双人皮划艇的两个人如果体重相差太大就会沉没，现在问你总的最小不稳定值。

### 思路

我们可以枚举两个单独坐的人，然后用一个枚举剩下两个一起坐的人，不断的加上重量差，最后返回最终重量差，在所有返回的结果中取最小的，最后输出。

### 代码

枚举那两个使用单人皮划艇的人，然后看那 $2\times n-1$ 个人的最小不稳定值。

代码楼上 dalao 都讲过了，本蒟蒻就不在这里放了。

---

## 作者：Zikake (赞：0)

# 题目意思
有 $2\cdot n$ 个人，第 $i$ 个人重量为 $w_i$，有 $n+1$ 个皮划艇，其中，有 $n-1$ 个双人皮划艇，$2$ 个单人皮划艇，但是，双人皮划艇的两个人如果体重相差太大就会沉没，现在问你总的最小不稳定值。

# 思路
枚举那两个使用单人皮划艇的人，然后看那 $2\cdot(n-1)$ 个人的最小不稳定性值。

# ACcode
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=50;
int n,ans=LONG_LONG_MAX;
int a[2*N+10];
int ANS(int q,int w){
	int b[2*N+10],cnt=0;
	for(int i=1;i<=2*n;i++){
		if(i==q||i==w)continue;//选定的两个人不好能使用双人皮划艇 
		else b[++cnt]=a[i];
	}
	int sum=0;
	for(int i=1;i<=cnt;i+=2){
		sum+=b[i+1]-b[i];//统计不稳定性值 
	}
	return sum;
}
signed main(){
	ofstream out("data");
	cin>>n;
	for(int i=1;i<=2*n;i++){
		cin>>a[i];
	}
	sort(a+1,a+2*n+1);//排序 
	for(int i=1;i<=2*n;i++){//枚举两个人来使用单人皮划艇 
		for(int j=1;j<=2*n;j++){
			if(i==j)continue;//特判 
			ans=min(ans,ANS(i,j));//统计最小不稳定性值 
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```


---

## 作者：haozinojc (赞：0)

本题是一道非常简单的**枚举**题。


### 思路：

先用两个循环，将两个坐单人皮划艇的枚举出来，再在这个基础上将剩下的人排序，每两个人坐一个双人皮划艇，把总不稳定值算出来。因为是枚举，所以不断更新最小总不稳定值即可。


### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=110;
int n,w[N],ans=0x7f7f7f7f;
int a[N],len;
signed main(){
	cin>>n;
	for(int i=1;i<=2*n;i++)cin>>w[i];
	for(int i=1;i<=2*n;i++){
		for(int j=i+1;j<=2*n;j++){
			memset(a,0,sizeof(a));len=0;
			for(int l=1;l<=2*n;l++){
				if(l!=i&&l!=j){
					a[++len]=w[l];
				}
			}
			sort(a+1,a+1+len);
			int minn=0;
			for(int i=1;i<=len;i+=2){
				minn+=abs(a[i+1]-a[i]);
			}
			ans=min(ans,minn);
		}
	}
	cout<<ans;
	return 0;
} 
```


---

