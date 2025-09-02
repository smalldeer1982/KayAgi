# 题目信息

# Dead Pixel

## 题目描述

Screen resolution of Polycarp's monitor is $ a \times b $ pixels. Unfortunately, there is one dead pixel at his screen. It has coordinates $ (x, y) $ ( $ 0 \le x < a, 0 \le y < b $ ). You can consider columns of pixels to be numbered from $ 0 $ to $ a-1 $ , and rows — from $ 0 $ to $ b-1 $ .

Polycarp wants to open a rectangular window of maximal size, which doesn't contain the dead pixel. The boundaries of the window should be parallel to the sides of the screen.

Print the maximal area (in pixels) of a window that doesn't contain the dead pixel inside itself.

## 说明/提示

In the first test case, the screen resolution is $ 8 \times 8 $ , and the upper left pixel is a dead pixel. Here you can see one of two possible layouts of the maximal window.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1315A/cb58b5325ebfab8c891df37e110ee05ad36ccf9e.png)

## 样例 #1

### 输入

```
6
8 8 0 0
1 10 0 3
17 31 10 4
2 1 0 0
5 10 3 9
10 10 4 8```

### 输出

```
56
6
442
1
45
80```

# AI分析结果

### 题目内容
# 坏点

## 题目描述
Polycarp 的显示器屏幕分辨率为 $a \times b$ 像素。不幸的是，屏幕上有一个坏点。它的坐标为 $(x, y)$（$0 \leq x < a$，$0 \leq y < b$）。你可以认为像素列从 $0$ 到 $a - 1$ 编号，行从 $0$ 到 $b - 1$ 编号。

Polycarp 想要打开一个最大尺寸的矩形窗口，该窗口不包含坏点。窗口的边界应与屏幕的侧边平行。

输出不包含坏点的窗口的最大面积（以像素为单位）。

## 说明/提示
在第一个测试用例中，屏幕分辨率为 $8 \times 8$，左上角的像素是坏点。这里你可以看到最大窗口的两种可能布局之一。
![图](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1315A/cb58b5325ebfab8c891df37e110ee05ad36ccf9e.png)

## 样例 #1
### 输入
```
6
8 8 0 0
1 10 0 3
17 31 10 4
2 1 0 0
5 10 3 9
10 10 4 8
```
### 输出
```
56
6
442
1
45
80
```

### 算法分类
数学

### 题解综合分析与结论
这些题解思路基本一致，均是通过分析得出不包含坏点的最大矩形只可能在坏点的上、下、左、右四个方向，分别计算这四个方向矩形的面积并取最大值即为答案。不同点主要在于代码实现细节，如输入方式、坐标处理等。

### 所选的题解
- **作者：dingcx（5星）**
  - **关键亮点**：思路清晰，通过画图辅助理解，先直观展示可能的解区域，再推导出计算公式，代码简洁明了，直接套用公式求解。
  - **重点代码**：
```cpp
#include<cstdio>
#include<algorithm> //用到 max
using namespace std;
int read(){ //没啥用的快读
    int num=0,sign=1; char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')sign=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){num=num*10+ch-'0';ch=getchar();}
    return num*sign;
}
int main(){ //主函数
    int T=read(); //数据组数
    while(T--){
        int n=read(),m=read(),x=read(),y=read();
        printf("%d\n",max(max(x,n - x - 1)*m,max(y,m - y - 1)*n)); //直接套公式
    }
    return 0; //华丽结束
}
```
  - **核心实现思想**：利用快读读取数据，通过公式 `max(max(x,n - x - 1)*m,max(y,m - y - 1)*n)` 直接计算并输出最大面积。

- **作者：sycqwq（4星）**
  - **关键亮点**：思路表述清晰，直接列举出死像素上、下、左、右四种情况对应的面积计算方式，代码逻辑简单易懂。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define inf 2147283647
using namespace std;
int main(){
    int t;
    cin>>t;
    for(int i = 1;i <= t;i++)
    {
        int a,b,x,y;
        cin>>a>>b>>x>>y;
        x += 1;//注意是从0开始，所以要+1
        y += 1;
        int s1=(y - 1)*a;//四种情况
        int s2=(b - y)*a;
        int s3=(x - 1)*b;
        int s4=(a - x)*b;
        cout<<max(max(max(s1,s2),s3),s4)<<endl;//最大的
    }
    return 0;
}
```
  - **核心实现思想**：读入数据后，将坐标加1以适应从1开始的计算习惯，分别计算四种情况的面积并取最大值输出。

- **作者：流绪（4星）**
  - **关键亮点**：简洁明了地指出是结论题，通过画图得出四种可能情况，代码实现规范，使用了 `max` 函数来获取最大面积。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
#define ri register int
#define il inline
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    int t;
    cin >> t;
    while(t--)
    {
        int a,b,x,y;
        cin >> a >> b >> x >> y;
        ll s1 = (a - x - 1)*(b);
        ll s2 = (a)*(b - y - 1);
        ll s3 = (a)*(y);
        ll s4 = (x)*b;
        s1 = max(s1,max(s2,max(s3,s4)));
        cout << s1 << endl;  
    }
    return 0;
}
```
  - **核心实现思想**：读入数据后，分别计算坏点四个方向矩形的面积，使用 `max` 函数获取最大面积并输出。

### 最优关键思路或技巧
通过对坏点位置的分析，发现不包含坏点的最大矩形只可能出现在坏点的上、下、左、右四个方向，从而将问题简化为计算这四个矩形的面积并取最大值，这种基于几何位置关系的分析思维是解决本题的关键。

### 拓展
同类型题通常围绕在给定区域内排除特定点或区域，求满足条件的最大或最小几何图形（如矩形、圆形等）的相关参数（如面积、周长等）。类似算法套路是通过对特殊点或区域的位置分析，确定可能的几何图形位置，进而计算相关参数。

### 推荐洛谷题目
- [P1046 陶陶摘苹果](https://www.luogu.com.cn/problem/P1046)
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)
- [P1192 台阶问题](https://www.luogu.com.cn/problem/P1192)

### 个人心得摘录与总结
无。 

---
处理用时：55.54秒