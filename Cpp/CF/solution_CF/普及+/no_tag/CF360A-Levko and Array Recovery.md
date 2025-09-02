# Levko and Array Recovery

## 题目描述

Levko loves array $ a_{1},a_{2},...\ ,a_{n} $ , consisting of integers, very much. That is why Levko is playing with array $ a $ , performing all sorts of operations with it. Each operation Levko performs is of one of two types:

1. Increase all elements from $ l_{i} $ to $ r_{i} $ by $ d_{i} $ . In other words, perform assignments $ a_{j}=a_{j}+d_{i} $ for all $ j $ that meet the inequation $ l_{i}<=j<=r_{i} $ .
2. Find the maximum of elements from $ l_{i} $ to $ r_{i} $ . That is, calculate the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF360A/b8abcd9e917cd04eb743a84b9d9be23896e61fc8.png).

Sadly, Levko has recently lost his array. Fortunately, Levko has records of all operations he has performed on array $ a $ . Help Levko, given the operation records, find at least one suitable array. The results of all operations for the given array must coincide with the record results. Levko clearly remembers that all numbers in his array didn't exceed $ 10^{9} $ in their absolute value, so he asks you to find such an array.

## 样例 #1

### 输入

```
4 5
1 2 3 1
2 1 2 8
2 3 4 7
1 1 3 3
2 3 4 8
```

### 输出

```
YES
4 7 4 7```

## 样例 #2

### 输入

```
4 5
1 2 3 1
2 1 2 8
2 3 4 7
1 1 3 3
2 3 4 13
```

### 输出

```
NO
```

# 题解

## 作者：wind_whisper (赞：0)

## $\text{Description}$
有一个长度为 $n$ 的序列 $a_{1...n}$，对其进行 $m$ 次操作，操作有两种：  
1. $1\space l_i\space r_i\space d_i$：对于 $l_i\le j\le r_i$，$a_j\gets a_j+d_i.$
1. $2\space l_i\space r_i\space m_i$：查询 $\max a_j(l_i\le j\le r_i).$  

现在给出 $n,m$ 和操作信息，请你构造出一种合法的序列或者报告无解.
## $\text{Solution}$
设第 $i$ 个元素**当前**的增量为 $add_i$，每个元素**初始**的最大值为 $mx_i$.  
每次对于操作二，$mx_j\gets \min(mx_j,m_i-add_j)(l_i\le j\le r_i)$.  
这样，把操作扫一遍就能求出所有元素的 $mx_i$.  
得出正确的 $mx_i$ 后，我们再扫一遍操作序列，对于每一次操作二，设 $w=\max mx_j(l_i\le j\le r_i)$.  
由于第一次维护的原因，必然有 $w\le m_i$.  
若 $w< m_i$，说明区间内的所有元素都达不到 $m_i$，报告无解.  
如果扫到最后还没有无解，输出 $mx_{1...n}$ 作为构造的序列. 
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=5005;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}
int n,m;
int mx[N],add[N];
struct query{
  int op,l,r,x;
}q[N];
int main(){
  #ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();m=read();
  memset(mx,0x3f,sizeof(mx));
  for(int i=1;i<=m;i++){
    q[i]=(query){(int)read(),(int)read(),(int)read(),(int)read()};
    if(q[i].op==1){
      for(int j=q[i].l;j<=q[i].r;j++) add[j]+=q[i].x;
    }
    else{
      for(int j=q[i].l;j<=q[i].r;j++) mx[j]=min(mx[j],q[i].x-add[j]);
    }
  }
  memset(add,0,sizeof(add));
  for(int i=1;i<=m;i++){
    if(q[i].op==1){
      for(int j=q[i].l;j<=q[i].r;j++) add[j]+=q[i].x;
    }
    else{
      int o=-2e9;
      for(int j=q[i].l;j<=q[i].r;j++) o=max(o,mx[j]+add[j]);
      if(o!=q[i].x){
	printf("NO\n");return 0;
      }
      //printf("i=%d o=%d\n",i,o);
    }
  }
  printf("YES\n");
  for(int i=1;i<=n;i++) printf("%d ",min(mx[i],1000000000));
  return 0;
}

```


---

