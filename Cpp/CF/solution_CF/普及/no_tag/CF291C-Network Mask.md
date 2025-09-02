# Network Mask

## 题目描述

## 题目背景

该问题使用了一个简化的TCP/IP地址模型，请确保您仔细阅读了该声明。


Polycarpus找到了一份工作，他是一名系统管理员。

有一天他偶然发现了n个IP地址。

每个IP地址是一个32位的数字，用4个8位数字(不带前导零)组成一组，用点分隔。

例如，记录0.255.1.123显示正确的IP地址，记录0.256.1.123和0.255.1.01不正确。

在这个问题中，由4个8位数字组成的任意组就是一个正确的IP地址。

Polycarpus作为一名管理员工作了一段时间，了解到如果您知道IP地址，您可以使用子网掩码来获得拥有该IP地址的网络地址。

子网掩码是一个IP地址，它有以下属性:如果我们把这个IP地址写为一个32位的字符串，它可以表示为“11…11000..000”。

换句话说，子网掩码首先有一个或多个1位，然后是一个或多个0位(总共有32位)。

例如，IP地址2.0.0.0不是一个正确的子网掩码，因为它的32位记录看起来是0000001000000000000000000000。

要得到IP地址的网络地址，需要执行IP地址和子网掩码的按位“与”操作。

例如，如果子网掩码是255.192.0.0,IP地址是192.168.1.2，则网络地址等于192.128.0.0。

在按位的“与”中，当且仅当两个操作数对应的位都等于1时，结果的位等于1。

现在Polycarpus想要找到他的IP地址所属的所有网络。

不幸的是Polycarpus丢失了子网掩码。

幸运的是，Polycarpus记得他的IP地址完全属于 $k$ 种不同的网络。

帮助Polycarpus找到子网掩码，这样他的IP地址将完全属于 $k$ 种不同的网络。

如果有多个子网掩码，则查找位记录中1个数最少的一个。

如果不存在这样的子网掩码，输出-1。

## 样例 #1

### 输入

```
5 3
0.0.0.1
0.1.1.2
0.0.2.1
0.1.1.0
0.0.2.3
```

### 输出

```
255.255.254.0```

## 样例 #2

### 输入

```
5 2
0.0.0.1
0.1.1.2
0.0.2.1
0.1.1.0
0.0.2.3
```

### 输出

```
255.255.0.0```

## 样例 #3

### 输入

```
2 1
255.0.0.1
0.0.0.2
```

### 输出

```
-1
```

# 题解

## 作者：North_encounter (赞：6)

~~就是说 cf 怎么炸了~~

[题目传送门](https://www.luogu.com.cn/problem/CF291C)


---

## 题目大意
对于 $n$ 个地址，给出最小的一条子路掩码，按位与后使其能生成 $k$ 个网络地址，若不存在，则输出 $-1$。

## 思路

#### 1. 输入及处理

题目给出的地址之间有点分隔，对于一条地址，可以将它的四个部分分开输入，再进行处理。

#### 2. 模拟生成子路掩码

先将 dis 值赋为 $2^{32}-1$，在二进制下为一个长为 $31$，每一位都是 $1$ 的数，每循环一次删去从后往前将一个 $1$ 改为 $0$。

#### 3. 记录每条子路掩码可生成的网址数量

使用键值对记录每条网址是否出现过，记住每尝试一条新的子路掩码后要清空。

#### 4. 输出

要将其分为四段，每段八位（要对 $256$ 取余）。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=100001;
int n,k;
int ans=-114514;
int cnt;
unsigned dis=UINT_MAX;//大小即为 2^32-1 
int m[N];//每一位的 IP 地址 
map<int,int> vis;//是否记录过 
signed main(){
//	ios::sync_with_stdio(false);	//不可使用！ 
//	cin.tie(0);
//	cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		int a,b,c,d;
		cin>>a,getchar();
		cin>>b,getchar();
		cin>>c,getchar();
		cin>>d;
		m[i]=(a<<24)+(b<<16)+(c<<8)+d;//将四个八位数字转为一个三十二位数字 
	}
	for(int i=1;i<=31;i++){
		dis-=(1<<i-1);
		for(int j=1;j<=n;j++){
			if(!vis[m[j]&dis]){//如果没出现过 
				vis[m[j]&dis]=1;
				cnt++;
			}
		}
		if(cnt==k){//满足条件 
			ans=dis;//记录 
		}
		vis.clear();//清空 
		cnt=0;
	}
	if(ans==-114514){
		cout<<-1<<endl;
		return 0;
	}else{
		cout<<((ans>>24)%256)<<"."<<((ans>>16)%256)<<"."<<((ans>>8)%256)<<"."<<(ans%256)<<endl;
		//按位分割输出 
	}
	return 0;
}
```

整体上就是模拟，与楼上两位巨佬思路挺像，当然，本题中的子网掩码可以正着构造，也可以倒着。

题外话：以此来记载 CSP-S 2024 惨败，并警示其他 OIer 一定要把所有样例跑一遍，不要只试最大的！

 _graceful_

 2024.12.19 更改了某一位是零时的错误，感谢 [Shizaki_Crazy_Three](https://www.luogu.com.cn/user/845988) 的指正

---

## 作者：liuzhongrui (赞：2)

## 思路

读取 $n$ 个地址，将它们转换为 $32$ 位的数字表示。接下来，使用一个循环尝试不同的子网掩码，统计每个子网掩码对应的网络数量。如果找到了一个子网掩码，使得网络数量等于 $k$，则更新答案。最后，输出找到的子网掩码，如果不存在这样的子网掩码，输出 ```-1```。

## Code

```cpp
#include<bits/stdc++.h>
#define gc getchar()
#define ll unsigned
using namespace std;
int n,k;
ll A,b,c,d,ans=-1;
ll a[100010];
map<ll,bool> mp;
int main() {
	cin>>n>>k;
	for(int i=1; i<=n; i++) {
		cin>>A,gc;
		cin>>b,gc;
		cin>>c,gc;
		cin>>d;
		a[i]=(A<<24)+(b<<16)+(c<<8)+d;
	}
	ll now=UINT_MAX;
	for(int i=1; i<=31; i++) {
		now-=(1<<i-1);
		int cnt=0;
		mp.clear();
		for(int j=1; j<=n; j++) if(!mp[now&a[j]]) mp[now&a[j]]=1,cnt++;
		if(cnt==k) ans=now;
	}
	if(ans==-1) cout<<"-1";
	else cout<<((ans>>24))<<"."<<((ans>>16)&255)<<"."<<((ans>>8)&255)<<"."<<(ans&255);
	return 0;
}
```


---

## 作者：OIerZhao_1025 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF291C)

## 思路
读取 $n$ 个地址，将它们转换为数字表示。接下来，统计每个子网掩码对应的网络数量。如果找到了一个子网掩码，使得网络数量等于 $k$，则更新答案。最后，输出子网掩码。\
首先输入的以后要注意把他的四个分开，我们要边输入边分开，这里可以用 map 来存储。
> map 是标准模板库中的一个关联容器，它存储的是键值对，并且按照键的升序进行排序

## code
```cpp
	for(int i=1;i<=31;i++)
    {
		d-=(1<<i-1);
		for(int j=1;j<=n;j++)
        {
			if(!vis[m[j]&d])
            {
				vis[m[j]&d]=1;
				cnt++;
			}
		}
		if(cnt==k)ans=d; 
		vis.clear(); 
		cnt=0;
	}
```

---

## 作者：L_shadow (赞：0)

## 思路：
主要是**模拟**。

边输入边处理，将输入的四个数转化为一个 $32$ 位数，方便计算。

然后，根据位数从大到小在二进制下将该位改为 $1$ （即生成合法的子关掩码），并用此时的子关掩码扫描所有IP地址，统计生成网络数量，如果生成网络数量恰好等于 $k$ ，输出并终止程序，防止重复输出。

时间复杂度为 $\Theta(n\log n)$ ，比较优秀。

### 易错点：
统计生成网络数量时，不能用数组，需要用map。因为此时生成的网络有 $2^{32}-1$ 个，如果使用数组，会爆空间或者统计错误。

## code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,tot;
int a[100005];
map <long long,bool> vis;
long long ksm(long long a,long long b){
	long long res=1;
	while(b){
		if(b&1) res*=a;
		a*=a;
		b>>=1;
	}
	return res;
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		int a1,a2,a3,a4;
		scanf("%d.%d.%d.%d",&a1,&a2,&a3,&a4);
		a[i]=(long long)(a1<<24)+(long long)(a2<<16)+(long long)(a3<<8)+a4;
	}
	long long ans=0;
	for(int i=31;i>=1;i--){
		ans+=ksm(2,i);
		tot=0;
		for(int j=1;j<=n;j++){
			if(!vis[ans&a[j]]){
				tot++;
				vis[ans&a[j]]++;
			}
		}
		vis.clear();
		if(tot==k) {
			printf("%lld.%lld.%lld.%lld",ans>>24,(ans>>16)&255,(ans>>8)&255,ans&255);//处理一下再输出。 
			return 0;
		}
	}
	cout<<-1;
	return 0;
}

```


---

