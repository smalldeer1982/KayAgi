# haruki、気になります！

## 题目描述

有一天，haruki先生在学校学了素数。所谓素数，是指只有1和本身两个因数的整数。

非常好奇心旺盛的haruki先生有以下疑问。

“n以下的素数中有几个偶数呢？”haruki很在意！

因此，请为haruki先生创建一个程序，求出在n以下的素数中有几个偶数。

## 样例 #1

### 输入

```
3```

### 输出

```
1```

# 题解

## 作者：不到前10不改名 (赞：3)

又是at水题，又是我，这题绝对水，一开始还认为是筛法去2，没想到~
```
#include<stdio.h>
int main()
{
    int n;
    scanf("%d",&n);
    if(n<2)
    printf("0\n");//没什么好说的，回车了解一下?
    else 
    printf("1\n")
}
```

---

## 作者：CZQ_King (赞：2)

# 不偷懒系列

------------
思路：线筛$+$数组查找

------------
代码：
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
int a,ans;
bool s[105]={1,1};//先把0和1赋值为不是质数
int xs(int a){//线筛不多说
    for(int i=2;i<=sqrt(a);i++){
        if(s[i]==0){
            for(int j=i*2;j<=a;j+=i)s[j]=1;
        }
    }
}
int main(){
    cin>>a;//输入a
    xs(a);//线筛
    for(int i=0;i<=a;i++){
        if(s[i]==0&&i%2==0)ans++;//如果是质偶数
    }
    cout<<ans<<endl;//输出答案
    return 0;//结束
}
```

---

## 作者：wubaiting2020 (赞：2)

题意：求小于n的素数中有多少个偶数


------------
思路：因为所有素数中只有2是偶数，所以只需判断n是否小于2即可。


------------

代码：
```
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
    int n;
    cin>>n;
    if(n<2)cout<<0<<endl;
    else cout<<1<<endl;
}
```

---

## 作者：封禁用户 (赞：0)

py简易题解

真的，这题建议隐藏。。。
```python
a=eval(input())
if(a<2):
    print(0)
else:
    print(1)
```

---

