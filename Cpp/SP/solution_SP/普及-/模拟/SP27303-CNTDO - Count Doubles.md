# CNTDO - Count Doubles

## 题目描述

给你一个整数数组，您的任务是确定数组中的某个整数是同一数组中其他整数的两倍的数的个数。例如，考虑一个数组 $a=\{1,3,4,7,9,2,18\}$，答案是 $3$，因为 $2$ 是 $1$ 的两倍，$4$ 是 $2$ 的两倍， $18$ 是 $9$ 的两倍。

# 题解

## 作者：天绝 (赞：1)

# 思路
  其实将题意翻译一下就是，给你一列数，找出里面符合2倍关系的个数。
           
      比如1 3 4 7 9 2 18，那么答案便为3.很显然是（1与2）（2与4）（9与18）。。
 我们粗略地看一眼数据：每个数的绝对值小于等于10000！那貌似可以用桶做吧，将每个数当做下标存入数组，当判断时只需要判断以某数2倍为下标的数组是否存在即可。(f[2*a[i]]==1)
   
   最后还需要注意一点，就是负数的情况，因为肯定大于-10000嘛~，所以同时加上10001即可，不会影响最后的结果。
   
------------

# 代码
 ```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int f[20010],a[2000],n,i,m,ans;
int main() 
{
    scanf("%d", &n);//读入数据
    for(int j=1;j<=n;j++)
    {
        ans=0;
        scanf("%d",&m);
        for(i=1;i<=m;i++)
        {
            scanf("%d",&a[i]);
            f[a[i]+10001]=1;
        }//用下标统计每一个数字
        for(i=1;i<=m;i++)
        {
            if(a[i]>5000 || a[i]<-5000) continue; 
            if(f[2*a[i]+10001]) ans++; //判断它的两倍是否存在，存在即+1
        } 
        memset(f,0,sizeof(f));//数组清零
        printf("%d\n", ans);//输出
    }
    return 0;//本人亲测可过quq
}//偶然的瞬间，你会意识到某些东西早已不像以前。在与他人接触的时候，总会无意地在心底思考，默默地质问自己“这样做是对的吗？”
```


---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/SP27303)      
我们建一个桶，称为 $flag$。$flag_i$ 表示 $i$ 是否在 $a$ 中存在，如果存在就是 $1$，否则为 $0$。         
之后我们对于每个 $a_i$，如果 $a_i\times 2$ 存在，结果就加上 $1$。     
本题有负数的情况，所以我们要稍微改一改。    
$flag_{i+20000}$ 代表 $i$ 有没有存在，判断的时候我们用 $a_i\times2+20000$ 这个数来判断就可以。    
CODE：     
```cpp
//Code by __dest__ruct__or__(uid=592238)
#include <iostream>
#include <cstring>
using namespace std;
#define umap unordered_map
#define ll long long
namespace mySTL{
	inline int max(int a,int b){return a>b?a:b;}
	inline int min(int a,int b){return a<b?a:b;}
	inline int abs(int a){return a<0?-a:a;}
	inline int read(){char c=getchar();int f=1,ans=0;
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9')ans*=10,ans+=c-'0',c=getchar();
	return ans*f;}
	inline long long readll(){char c=getchar();long long f=1,ans=0;
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9')ans*=10,ans+=c-'0',c=getchar();
	return ans*f;}
	inline void swap(int &a,int &b){a^=b,b^=a,a^=b;}
	inline void write(int x){if(x<0){putchar('-');x=-x;}
	if(x>=10){write(x/10);}putchar(x%10+'0');}
	inline void writell(long long x){if(x<0){putchar('-');x=-x;}
	if(x>=10){write(x/10);}putchar(x%10+'0');}
}
using namespace mySTL;
int t,n,a[1010],ans;
bool flag[100000];
int main(void){
	//freopen("data.txt","r",stdin);
	t=read();
	while(t--){
		ans=0;//多测要清空
		memset(flag,0,sizeof(flag));
		n=read();
		for(int i=1;i<=n;i++){
			a[i]=read();
			flag[a[i]+20000]=true;//标记
		}
		for(int i=1;i<=n;i++){//计算结果
			ans+=flag[a[i]*2+20000];
		}
		write(ans);
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：yyyh_h (赞：0)

# 题意
先输入 $T$ ，表示数据组数，每组数据输入 $n$ ，再输入 $n$ 个数，输出这些数中有 $2$ 倍关系的关系总数。

例：
```
1
9
1 2 4 5 7 3 9 14 18
答案：4
```
# 思路
这道题目中，对于每组数据我们只需要建一个 ```map<int,bool>``` 容器类型的 $f$ 并将读入的 $n$ 个数分别标记为 $1$ ，这样可以很好的解决数组下标无法为负数的问题。然后，我们再将 $n$ 个数扫一遍，看看这些数的 $2$ 倍是否也被标记为 $1$ ，如果有就将答案加 $1$ .
# 代码
```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
int T; 
int a[1010];
int main()
{
	scanf("%d",&T);//读入数据组数。 
	while(T--)//循环T次。 
	{
		memset(a,0,sizeof(a));//每组数据要清空a数组。 
		map<int,bool>f;//开map，不然存不了负数 。 
		int n,ans=0;//ans注意清零。 
		scanf("%d",&n);//读入n。 
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);//读入n个数。 
			f[a[i]]=1;//对每个数进行标记。 
		}
		for(int i=1;i<=n;i++)
		{
			if(f[2*a[i]]==1)//判断a_i的2倍是否也在a数组中。 
			{
				ans++;//有就把答案加1。 
			}
		}
		printf("%d\n",ans);//输出答案，但是注意要换行。 
	}
	return 0;//完结撒花！ 
}
```



---

