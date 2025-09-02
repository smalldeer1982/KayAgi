# Valera and X

## 题目描述

Valera是一个小男孩。昨天，他的数学作业很多，因此他没有时间去温习英语课的单词表。不幸的是，英语老师决定在今天的课上进行一场单词小测。测试中，发下的试卷是正方形的，由许多小格子组成，共有n行n列（n是奇数），每个单位的小格子都包含一个英文字母。

Valera需要知道试卷上的小字母是否会组成一个大写字母“X”的形状。Valera的老师认为试卷上的字母会构成“X”，当且仅当：

1、所有对角线上的格子所包含的字母必须一致。

2、其他所有格子（不在对角线上的），也必须由相同的字母所组成且这个字母不能与对角线上的字母相同。

请你按照题面描述，编程帮Valera解决这个问题。

## 样例 #1

### 输入

```
5
xooox
oxoxo
soxoo
oxoxo
xooox
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
3
wsw
sws
wsw
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
3
xpx
pxp
xpe
```

### 输出

```
NO
```

# 题解

## 作者：qinyubo (赞：2)

[题目链接](https://www.luogu.com.cn/problem/CF404A)

大概题意：给你一个 $n\times n$ 的字符阵，要你判断是否满足下列三个条件：

- 两条对角线上的字符一样

- 其他部分的字符一样

- 对角线和其他部分字符不一样

这题是个模拟题，只需要按照题意模拟即可

首先我们双重循环，判断对角线的字母是否相等：
```cpp
for (int i = 1; i <= n; i++) {
    if (c[i][i] != c[1][1] || c[i][n - i + 1] != c[1][1]) {
        ans = "NO";
    }
}
```
然后再判断其他位置是否相等：
```cpp
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
        if (i != j && i + j != n + 1 && c[i][j] != c[1][2]) {
            ans = "NO";
        }
    }
}
```
最后别忘了对角线和其他部分要不一样：
```cpp
if (c[1][1] == c[1][2]) ans = "NO";
```
然后这个题就没啦！

上代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace QYB {
    int n; char c[305][305];
    int main() {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%s", c[i] + 1);
        } string ans = "YES";
        for (int i = 1; i <= n; i++) {
            if (c[i][i] != c[1][1] || c[i][n - i + 1] != c[1][1]) {
                ans = "NO";
            }
        } for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i != j && i + j != n + 1 && c[i][j] != c[1][2]) {
                    ans = "NO";
                }
            }
        } if (c[1][1] == c[1][2]) ans = "NO";
        return !printf(ans.c_str());
    }
} int main() {
    return QYB::main();
}
```

---

## 作者：LYR_ (赞：1)

### 题意： 
有一个字符方阵，如果这个方阵两个对角线上的字母都相同，并且其余字母都相同，那么输出YES，否则输出NO

### 思路：
- 根据题意得，方阵中的字母只有两种，所以可以使用set容器 [（具体用法）](https://blog.csdn.net/shuaizhijun/article/details/88955081)，因为set可以去重。将输入的每一个字符都添加到set中（用insert），最终判断set的长度是否为2，如果不是2，输出NO
 
#####  _别看上面这段字很长，但实现起来很容易，效果是减少时间复杂度_
 
 - 然后就很简单了，判断两个对角线上面字母是否相同，如果不是，输出NO
 
 这个方法复杂度大约为 $O(N^{2})$，但没有关系，数据范围为 $3\le N\le 300$
 
### C++代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=310;
char c[N][N];
int main() {
    int n;
    cin>>n;
    set<char> s;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++) {
            cin>>c[i][j];
            s.insert(c[i][j]); //输入，并将字母插入set
        }
    if(s.size()!=2) { //判断set长度是否为2
        cout<<"NO"<<endl;
        return 0;
    }
    char t;
    t=c[0][0];
    bool f=1;
    for(int i=1;i<n;i++) { //判断从左到右的对角线的第一位与其他位是否相同
        if(c[i][i]!=t) {
            f=0;
            break ;
        }
    }   
    if(!f) {
        cout<<"NO"<<endl;
        return 0;
    }     
    for(int i=0;i<n;i++) { //判断从右到左的对角线的第一位与其他位是否相同
        if(c[i][n-i-1]!=t) {
            f=0;
            break;
        }
    }
    if(!f) {
        cout<<"NO"<<endl;
        return 0;
    }
    for(int i=0;i<n;i++) { //判断其他格子是否都相同
        for(int j=0;j<n;j++) {
            if(i!=j && i!=n-j-1 && c[i][j]==t) {
                f=0;
                break;
            }
        }
    }
    if(!f) {
        cout<<"NO"<<endl;
        return 0;
    }
    cout<<"YES"<<endl;
    return 0;
}
```
防疫在家，做做贡献，求赞

---

## 作者：灵光一闪 (赞：0)

这题无非就是判断

首先！

1. 当(0,0)和(0,1)相等时，就不可能是个X；

1. 当两条对角线上不是两两相等的时候：NO；

1. 当其他格子有不同的时候，NO；

解决：（只给核心代码：  
1:
```
    if(c[0][0]==c[0][1]){//简单明了快捷
        puts("NO");
        return 0;
    }
```
2:
```
    char check=c[0][0];//标准
    for(int i=0;i<n;i++){
        if(c[i][i]!=check||c[n-i-1][i]!=check){
            puts("NO");//一旦不符合标准就是NO
            return 0;
        }
        c[i][i]=c[n-i-1][i]=c[0][1];//这里等下讲一下
    }
```
3:
```
    check=c[0][1];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(c[i][j]!=check){//看到木有？上面的赋值的意思是这样的：既然保证了不是整张图全等，那么直接把所有的统一起来，方便判断
                puts("NO");
                return 0;
            }
        }
    }
```
最后就是YES，然后就return 0;

The End.

---

## 作者：221B (赞：0)

~~代码有点长，介意的小伙伴请跳过函数部分~~

咳咳，进入正题。这道题本蒟蒻的思路大致是：将对角线上的一个字母与非对角线上的一个字母储存起来，再一个一个查找对角线上的字母和非对角线上的字母，如果查找到的字母与已储存的字母不同，就输出“NO”，如果都相符，输出“YES”。

**注意点：**

 _**1.对角线有两条（从左上到右下的对角线和从右上到左下的对角线），所以要一一判断。**_ 

 _**2.有可能整个二位数组中的字母都是一样的，但这并不能构成一个“X”，需要剔除。**_ 

本蒟蒻只能为各位大佬提供如上简陋的思路了，另附AC代码详解：
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
char a[1001][1001];//定义二位数组
int n;
inline int read(){//快读，比cin和scanf都要快（NOIP利器）
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
void p_x(){//自己写的输出函数，比较方便
    printf("NO");//输出NO的函数
    exit(0);//结束整个程序（如果用return 只能终止这个函数）
}
void p_y(){//输出NO的函数
    printf("YES");
    exit(0);
}
int main(){
    char c1,c2;
    n=read();//用快读读入n
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
        cin>>a[i][j];//读入二维数组
    }
    c1=a[1][1];//将对角线上的某一个字母储存（不一定是a[1][1]，只要是在对角线上的就行）
    c2=a[1][2];//将非对角线上的某一个字母储存（只要是非对角线上的就行）
    int f=0;
    for(int i=1;i<=n;i++){//注意这个点！有可能整个二位数组都是一个相同的字母！但它并不能组成一个“X”
    	for(int j=1;j<=n;j++){
    		if(a[i][j]!=c1){//如果有一个字母不同于已储存的字母
    			f=1;//代表整个二维数组不是同一个字母
    			break;
			}
		}
		if(f==1)break;
	}
	if(f==0){//如果都是同一个字母
		p_x();//输出NO
	}
    for(int i=1;i<=n;i++){
    	for(int j=1;j<=n;j++){
    		if(i==j){//如果找到这个字母在从左上到右下的对角线上
    			if(a[i][j]!=c1)//如果不同于已储存的在对角线上的字母
    			p_x();//输出NO
			}
			else if(j==n-i+1){//如果找到的这个字母在右上到左下的对角线上
				if(a[i][j]!=c1)//同上
				p_x(); 
			}
			else {//如果这个字母不在对角线上
				if(a[i][j]!=c2)//如果这个字母不同于已储存的在非对角线上的字母
				p_x();//输出NO
			}
		}
	}
	p_y();//经过一系列考验，输出YES
    return 0;//养成好习惯
}
```


---

