# DIY Wooden Ladder

## 题目描述

**PS:此翻译对原题意进行了修改。**  
有$n$个数，依次为$a_1,a_2,a_3...a_n$。  
然后你可以从中选出$k+2$个数（$k$为任意正整数）。  
对于这$k+2$个数字，要满足第二大的数字至少比$k$大$1$。  
问最大的符合条件的$k$为多少。

## 样例 #1

### 输入

```
4
4
1 3 1 3
3
3 3 2
5
2 3 3 4 2
3
1 1 2
```

### 输出

```
2
1
2
0
```

# 题解

## 作者：Konnyaku_ljc (赞：6)

## 注意事项——
- 要使梯子最长，必须拿最长的两根木头当梯子的两根杆  
- 梯子杆长度必须大于1，不然一个也安不上！  
- 完成后，一定是min(a[n-1]-1,n-2)!MIN!
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int T,n,a[100005];
int main()
{
        cin>>T;
        while(T--)
        {
	    	cin>>n;
	    	for(int i=1;i<=n;i++) cin>>a[i];
	    	sort(a+1,a+1+n);//排序以选取最大值
	    	if(a[n-1]==1)cout<<"0"<<endl;
  	        //第二大的是1的时候，输出0
            //第一大的不需要判断
    	    //如果第一大是1，第二大一定也是
		    else 
		    {
	        	cout<<min(a[n-1]-1,n-2)<<endl;
            	//输出两者较小的那一个
		    }
        }
        return 0;
}
```

完美ACCEPT！

---

## 作者：风格雨关 (赞：3)

~~签到题~~   
题面:[传送门](https://www.luogu.org/problemnew/show/CF1197A)   
 _看题两小时，代码 $5$分钟 $QAQ$_    
想了一个简单的贪心,我们为了把梯子搭的高，则左右两根木棒一定要最长,就像这样：  
![](https://cdn.luogu.com.cn/upload/pic/65260.png)   

于是答案有两种可能：
1. 棍子足够多,就是塞不下,能塞几根就有几阶
2. 棍子不够多,剩下几个就有几阶

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int main(){
  int T;
  cin>>T;
  while(T--){//T组输入
    int n;
    cin>>n;
    int ma1=-1,ma2=-1;//记录两根最长的
    for(int i=0;i<n;i++){
      int k;
      cin>>k;
      if(k>=ma1){
        ma2=ma1;
        ma1=k;
      }
      else if(k>=ma2&&k<ma1) ma2=k;
    }
    cout<<min(ma2-1,n-((ma1==-1)?0:1)-((ma2==-1)?0:1))<<'\n';
    //ma2-1表示最多能塞下几根，表示第一种情况
    //n-((ma1==-1)?0:1)-((ma2==-1)?0:1)表示还剩下几根，因为有可能n<4,所以要加后面那串
    
  }
  return 0;
}

```


---

## 作者：Eismcs (赞：3)

这道题主要是意思很难理解，理解了就很简单了。

用前缀和，记录每个数，大于等于它的有多少个（像是一个桶）对于答案，暴力枚举，根据题意判断是否可以

具体构造前缀和嘛，排一下序，扫一遍即可
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<queue>
#include<map> 
using namespace std;
#define re register int
 
inline int read(){
    int x=0,ff=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')ff=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*ff;
}
int a[100005],b[100005];
signed main(){
    int t=read(),n,x,u;
    while(t--){
    	memset(b,0,sizeof(b));
    	n=read();
    	for(int i=1;i<=n;i++)a[i]=read();
    	sort(a+1,a+n+1);//排序
		x=n;bool kl=1;
		for(int i=a[n];i>=1;i--){
			b[i]=b[i+1];
			while(x>0&&i==a[x]){x--;b[i]++;}
        //前缀和的构造
		}
		for(int i=a[n];i>=1;i--){
        //暴力枚举，简单的判断
			if(b[i+1]>=2&&b[1]-2>=i){
				u=i;printf("%d\n",u);kl=0;break;
			}
		}
		if(kl)printf("0\n");
    }
    return 0;
}
```
所以读懂题目，是这题的关键

---

## 作者：Luban (赞：2)

前言：昨天晚上终于有空肝CF了，花了5分钟解决了T-A，又花了20分钟解决了T-B，结果想了20分钟T-C没有思路，于是就睡觉去了

于是，今天就来抢占第一发题解

## 这道题真实难度：普及-

思路：因为所有木板长度都>=1，所以the steps of the ladder只要随便取k块木板就可以了。the base of the ladder需要两块长度为k+1的，所以k<=第二长的木板的长度-1。但是我们还需要注意的是，需要k+2块木板才能搭成梯子，所以k<=n-2。为了防止答案为负数，保险起见，加上一句max语句

## 所以答案就是max(0,min(第二长的木板的长度-1,n-2))

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005];
int main()
{
	int t,n;
	cin>>t;
	while(t--)
	{
		cin>>n;
		int i=1,r=-1,t;
		while(i<=n)
		{
			cin>>a[i];
			if (r<a[i])
			{
				r=a[i];
				t=i;
			}
			i++;
		}
		i=1;
		r=-1;
		while(i<=n)
		{
			if (r<a[i]&&i!=t) r=a[i];//如果这不是最长的木板，更新答案
			i++;
		}
		cout<<max(0,min(n-2,r-1))<<endl;//最终输出
	}
	return 0;
}
```


---

## 作者：寒鸽儿 (赞：0)

我们要做的就是构造出解。  
k最大能到多少呢?至多到比第二小的数小一。否则不满足题意。这是必要条件。  
然后我们要选出k+2个数,意味着k <= n-2,否则数字根本不够选。  
取二者最小值即为答案。  
```cpp
#include <cstdio>

using namespace std;

inline int min(int x, int y) { return x < y ? x : y; }

int main() {
	int t, n, m1, m2, tmp;
	scanf("%d", &t);
	while(t--) {
		m1 = -1; m2 = -1;
		scanf("%d", &n);
		for(int i = 0; i < n; i++) {
			scanf("%d", &tmp);
			if(tmp >= m1) {
				m2 = m1; m1 = tmp;
			} else if(tmp > m2) {
				m2 = tmp;	
			}
		}
		printf("%d\n", min(m2-1, n-2));
	}
	return 0;
}
```

---

## 作者：xh39 (赞：0)

我们要k尽可能大,要尽可能选大的数。

之后可以发现:无论选几个比第二大小的数,第二大的不变,于是我们只需要找到第二大的数就可以了。

怎么查找第二大的数呢?如果要排一遍序,显得非常的麻烦,而且非常的耗时。我们可以记录两个变量,一个是第一大的,一个是第二大的。

如果当前输入的数比最大的还要大,更新最大的,旧的最大值就变成了次大值,更新次大值。

如果当前输入的介于次大值和最大值之间(**一定不能比最大值大**),就更新次大值。

把数组遍历完,次大值就找到了。这里看似最大值没有用,可需要它来保证次大值不和最大值重复。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t,n,i,j,k,a,max1,max2; //max1:最大值 max2:次大值。
    cin>>t;
    for(i=1;i<=t;i++){
        cin>>n;
        max1=0; //多组数据记得赋值。
        max2=0;
        for(j=0;j<n;j++){
            cin>>a;
            if(a>max1){
                max2=max1; //先赋值,不然更新的就是新的最大值
                max1=a;
            }else if(a>max2){
                max2=a;
            }
        }
        k=min(max2-1,n-2); //注意至多只能到n-2,不然就取不了了。
        cout<<max(0,k)<<endl; //如果比0小,就是没有符合要求的数,所以对0取最大值。
    }
    return 0;
}
```

---

## 作者：yizr_cnyali (赞：0)

因为梯子的"基础",即两旁的木棍中短的那根越长,那么梯子能使用的楼梯级数越多,容易相当可以贪心的解决。  
首先对所有的木棍按长度进行降序排序，那么用最长的2根木棍作为"基础"可以使级数最多，因此取第二长的那根作为"基础"的长度。由于长度为$n$的木棍只能在上面搭建$n-1$个楼梯，所以计算时需要将第二长的木棍长度减去1.    
现在已经知道了可以搭建的楼梯数目的最大值，但是我们并不知道剩余的木棍数目够不够搭建这么多楼梯，因此，还需要进行一次判断:如果剩余的木棍足够搭建这么多楼梯，那么这就是答案，否则，最大的楼梯级数为剩余的木棍数。
```cpp
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
 
using namespace std;
 
template <typename T> inline int Chkmax (T &a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> inline int Chkmin (T &a, T b) { return a > b ? a = b, 1 : 0; }
 
template <typename T> inline T read(){
    T sum = 0;
    int fl = 1,ch = getchar();
    for(; !isdigit(ch); ch = getchar()) if(ch == '-') fl = -1;
    for(; isdigit(ch); ch = getchar()) sum = (sum << 3) + (sum << 1) + ch - '0';
    return sum * fl;
}
 
const int maxn = 100000 + 5;
 
int T,n;
int a[maxn];
 
int main(){
    T = read<int>();
    while(T--){
        n = read<int>();
        for(int i = 1; i <= n; i++){
            a[i] = read<int>();	
        }
        sort(a + 1, a + n + 1,greater<int>());
        int tmp = a[2] - 1,ans = 0;
        if(n - 2 < tmp){
            ans = n - 2;	
        }else ans = tmp;
        printf("%d\n",ans);
    }
    return 0;
}
```


---

## 作者：NKL丶 (赞：0)

## 由于是要选出$k+2$个数字，然后又跟第二大的数字有关系，所以先对$a$数组进行一次排序。  
接下来分类讨论：
- 如果第二大的数字比剩下的数字个数还要大（即这个数$>n-2$）  
那么应该输出$n-2$；
- 如果第二大的数字比剩下的数字个数要小（即这个数$<n-2$）
那么应该输出第二大的数字$-1$；
- 如果$n$为$2$，那么最终的答案与第二大的数字无关，直接输出$0$。  

之所以要提到第二大的数字与$n-2$的大小关系，可以这样证明：
- 首先不难证明，选择大的数字作为会使得$k$的范围变大。
- 然后，也容易证明$k$的范围与第一大的数字无关，与第二大的有关。
- 那么因为要$k$最大，那么就尽量将剩下的数字都选上，可是因为$k <$第二大的数字，所以需要让$k$与第二大的数字进行比较。

知道了这些，这道题目的方法也就很容易知道了。  
附上代码：
```cpp
    #include<iostream>
    #include<cstdio>
    #include<algorithm>
    #include<cmath>
    using namespace std;
    int g,n,a[100000+5]; 
    int main()
    {
    	ios::sync_with_stdio(false);//加快cin,cout速度
    	cin>>g;//t组数据（我习惯用g表示）
    	while(g--)//等价于for(int i=1;i<=g;i++)
    	{
    		cin>>n;//输入
    		for(int i=1;i<=n;i++)cin>>a[i];
    		sort(a+1,a+1+n);//排序
    		if(a[n-1]-1<=n-2)cout<<a[n-1]-1<<endl;//分类讨论，注意要换行
    		else if(a[n-1]-1>n-2)cout<<n-2<<endl;
    		else cout<<0<<endl;
    	}
    	return 0;
    }
```


---

