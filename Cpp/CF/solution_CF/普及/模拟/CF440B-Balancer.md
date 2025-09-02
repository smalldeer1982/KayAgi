# Balancer

## 题目描述

---
佩蒂娅有 $k$ 根火柴，她要把这些火柴放在 $n$ 个火柴盒里。佩蒂娅希望所有盒子里的火柴数量相同，也就是每个火柴盒里面要放 $\frac kn$ 根火柴。她可以一步把 $1$ 根火柴从这个盒子里移到相邻的盒子里。问他需要多少次操作才能使得每个盒子都有 $\frac kn$ 根火柴。

## 样例 #1

### 输入

```
6
1 6 2 5 3 7
```

### 输出

```
12
```

# 题解

## 作者：L_zaa_L (赞：6)

## 分析
这道题是让我们将所有火柴盒里放入 $\frac{kn}{k}$ 个火柴，而且只能左右移动火柴。

可以从头开始想：第一个火柴盒左边没有火柴盒，就只能和第二个火柴盒进行移动，当第一个火柴盒有 $\frac{kn}{k}$，这时，第二个火柴盒只能和第三个进行移动（跟第一个火柴盒移动也没有什么用）……以此类推，就能完成。每次移动只用将多的给少的就行了。

## 答案
```
#include <bits/stdc++.h>
using namespace std;
long long k,n,a[20000002],ans; 
int main(){
	cin>>n;
	for(long long i=1;i<=n;i++){
		cin>>a[i];
		k+=a[i];
	}
	k/=n;
	for(long long i=1;i<=n;i++){
		a[i+1]+=(a[i]-k);
		ans+=abs(a[i]-k);
	}
	cout<<ans;
	return 0;
}
```
记得开 ```long  long```。

---

## 作者：CQ_Bab (赞：1)

# 思路
这道题其实很水，首先输入后你就可以把 $k$ 给求出来。然后我们就可以去遍历，用一个变量来记录答案然后将第 $i$ 位少的或是多的都交给 $i+1$ 位，这样就能保证第 $i$ 位及其之前的都等于 $\frac{k}{n}$(因为多的给了下一位少的让下一位给了你，最后保证了总数一定为 $k\times n$ 所以一定能分完），最后输出即可。
# AC代码
```
#include <bits/stdc++.h>
#define int long long
using namespace std ;
const int N=5e4+10;
int n,k,a[N],res;
signed main(){
  cin>>n;
  for(int i=1;i<=n;i++) {
    cin>>a[i];
  	k+=a[i];
  }
  k/=n; // 求平均值
  for(int i=1;i<=n;i++){
    if(a[i]<k) {
        a[i+1]-=(k-a[i]);// 将a[i]少的在a[i+1]减掉
        res+=abs(a[i]-k);//记录答案
    }else if(a[i]>k){
        a[i+1]+=(a[i]-k);// 将a[i]多的给a[i+1]
        res+=abs(a[i]-k);//记录答案
    }
  }
  cout<<res;
  return false; 
}
```


---

## 作者：N_z_ (赞：1)

## 思路
如果 $a_1$ 要变成 $\frac{k}{n}$ ，那么只能靠把多的给 $a_2$ 或从 $a_2$ 那里得到。

同理， $a_2$ 要变成 $\frac{k}{n}$ ，那么只能靠把多的给 $a_3$ 或从 $a_3$ 那里得到。

 $a_i$ 要变成 $\frac{k}{n} $，那么只能靠把多的给 $a_{i+1}$ 或从 $a_{i+1}$ 那里得到。

题目保证了所有数和是 $n$ 的整倍数。

即只有一个解。

直接模拟即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[50002];
signed main(){
    int n;
    cin>>n;
    int sum=0;
    for(int x=1;x<=n;x++)
    cin>>a[x],sum+=a[x];
    sum/=n;
    int ans=0;
    for(int x=1;x<=n;x++)
    ans+=abs(sum-a[x]),a[x+1]+=a[x]-sum;
    cout<<ans<<endl;
}

```

---

## 作者：DLDZD (赞：1)

## 思路：
首先把 $n$ 个数输入，然后累加到 $ans$ 中，从 $a[1]$ 到 $a[n]$ 中判断每一个和 $ans$ 相不相同，如果相同， $anss$ 减去 $a[i]$ 到 $ans$ 的距离， $a[i+1]$ 加上 $ans$ 到 $a[i]$ 的距离，重复 $n$ 次，最后输出，
## code：
```
#include<bits/stdc++.h>
using namespace std;
int a[50001],n,ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		ans+=a[i];//累加
	}
	ans/=n;//平均
	int anss=0;
	for(int i=1;i<=n;i++){
		int nn;//与ans差几
		if(a[i]!=ans){//若不相同
			anss+=abs(ans-a[i]);//减a[i]到ans的距离就是次数
		   a[i+1]+=a[i]-ans;//加ans到a[i]的距离就是次数
		}
	}
	cout<<anss<<'\n';//输出
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

## 思路
我们从头开始：第一个火柴盒左边是没有火柴盒的，所以就只能和第二个火柴盒进行移动，当第一个火柴盒有 $\frac{kn}{k}$ 时，第二个火柴盒只能和第三个进行移动，当第二个火柴盒有 $\frac{kn}{k}$ 时，第三个火柴盒只能和第四个进行移动。

以此类推，并在每次移动时将多的给少的即可。

## CODE 
```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

int k,n;
int ans;

int a[100000000]; 

signed main()
{
	cin>>n;
	
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		
		k+=a[i];
	}
	
	k/=n;
	
	for(int i=1;i<=n;i++)
	{
		a[i+1]=a[i+1]+(a[i]-k);
		
		if(a[i]<k)
		{
			ans+=k-a[i];
		}
		else
		{
			ans+=a[i]-k;
		}
	}
	
	cout<<ans;
	
	return 0;
}
```


---

