# [USACO20DEC] Daisy Chains B

## 题目描述

每天，作为她绕农场行走的一部分，奶牛 Bessie 会经过她最喜爱的草地，其中种有 $N$ 朵花（五颜六色的雏菊），编号为 $1\ldots N$（$1\le N\le 100$），排列成一行。花 $i$ 有 $p_i$ 朵花瓣（$1\le p_i\le 1000$）。

作为一名崭露头角的摄影家，Bessie 决定给这些花拍些照片。具体地说，对于每一对满足 $1\le i\le j\le N$ 的花 $(i,j)$，Bessie 会给从花 $i$ 到花 $j$ 之间的所有花（包括 $i$ 和 $j$）拍一张照。

后来 Bessie 查看这些照片时注意到有些照片里存在「平均」的花——一朵恰好有 $P$ 朵花瓣的花，其中 $P$ 等于照片中所有花的花瓣数量的平均值。

Bessie 的照片中有几张存在平均的花？ 

## 说明/提示

### 样例解释 1

每张仅包含一朵花的照片均会被计入答案（在这个样例中有 $4$ 张）。另外，在这个样例中 $(i,j)$ 为 $(1,2)$ 和 $(2,4)$ 所对应的照片也存在平均的花。 

## 样例 #1

### 输入

```
4
1 1 2 3```

### 输出

```
6```

# 题解

## 作者：2023gdgz01 (赞：3)

此题只需按题意模拟即可。我们可以枚举出拍照区间 $(i,j)$，然后加和算平均值，最后统计答案即可。时间复杂度 $O(n^3)$。

代码如下：

```cpp
#include <cstdio>

int n, ans, a[105], sum[105];
double temp;

int main() {
	scanf("%d", &n);
	for (register int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		sum[i] = sum[i - 1] + a[i]; //为了方便，我们使用前缀和，但时间复杂度相同
	}
	for (register int i = 1; i <= n; ++i) {
		for (register int j = i; j <= n; ++j) {
			temp = (sum[j] - sum[i - 1]) * 1.0 / (j - i + 1); //算平均值
			if (temp == (int)temp) //防止本来除不尽但是四舍五入的情况
				for (register int k = i; k <= j; ++k)
					if (a[k] == temp) {
						++ans;
						break; //有答案就 break
					}
		}
	}
	printf("%d", ans);
	return 0;
}
```
[AC 链接](https://www.luogu.com.cn/record/140059727)

---

## 作者：bitset_iTM (赞：0)

很简单的一道模拟题。  

### 思路：  
数据范围很小，怎么暴力怎么来。  
先双重循环枚举区间，通过前缀和 $O(1)$ 快速求得平均值，再枚举区间内每一个元素，若等于平均值则答案数加一，总复杂度 $O(n^3)$。

### Code：
```cpp
#include <bits/stdc++.h>
using namespace std;

int a[105], s[105];

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n && ("iYW" == "iYW"); i++)
    {
        scanf("%d", &a[i]);
        s[i] = s[i - 1] + a[i]; //前缀和
    }
    
    int res = 0;
    for (int l = 1; l <= n; l++)
        for (int r = l; r <= n; r++) //双重循环枚举区间
        {
            double avg = (s[r] - s[l - 1]) * 1.0 / (r - l + 1); //求平均值
            for (int i = l; i <= r; i++)
                if (a[i] == avg) //若相等，答案数加一
                {
                    res++;
                    break ;
                }
        }
    printf("%d\n", res); //Output The Answer.
    return 0; //Well Done!
}
```


---

## 作者：continueOI (赞：0)

简单题。

观察到数据范围，$1 \le N \le 100$，考虑直接暴力。

枚举所有二元组 $(i,j)$，求出其花瓣平均值，然后在暴力遍历判断是否存在花瓣数等于其平均值的花瓣。

如果数据范围大一点的话可以考虑用桶来优化，这里就不写了（~~因为懒~~）。

注意平均值要用浮点数形式储存。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int p[110];
int sum,ans;
double c;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>p[i];
	for(int i=1;i<=n;i++){
		sum=p[i];
		for(int j=i+1;j<=n;j++){
			sum+=p[j];
			c=1.0*sum/(j-i+1);
			for(int k=i;k<=j;k++){
				if(p[k]==c){
					ans++;
					break;
				}
			}
		}
	}
	cout<<ans+n;
	return 0;
}
```


---

## 作者：taojinchen (赞：0)

# 思路
依照题目模拟即可。其中在计算平均数的时候，可以用前缀和缩短计算区间和的代码，顺便降低时间复杂度。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long f[105],p[1005],i,j,ans,n;
double cnt;
int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n;
  for(i=1;i<=n;i++){
    cin>>f[i];
    f[i]+=f[i-1];//前缀和
  }
  for(i=1;i<=n;i++){
    for(j=i;j<=n;j++){
      p[f[j]-f[j-1]]++;//在[i,j]，有f[j]-f[j-1]朵花瓣的花有p[f[j]-f[j-1]]朵
      cnt=(f[j]-f[i-1])*1.00/(j-i+1.00);//防止精度丢失所以*1.00，并且j-i+1改成了j-i+1.00
      if(cnt==ceil(cnt)){//平均数是整数
        ans+=(p[(int)cnt]!=0);//至少有一朵恰好有（照片中所有花的花瓣数量的平均值）朵花瓣的花
      }
    }
    for(j=i;j<=n;j++){
      p[f[j]-f[j-1]]--;//清零
    }
  }
  cout<<ans;//输出
  return 0;
}
```


---

