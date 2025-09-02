# 题目信息

# Photographs (I)

## 题目描述

Heidi 组建的人牛联盟建造了一个防止僵尸攻击的基地, 基地的入口有一个安全门, 这个门执行一种测试, 它会向进入的人 (牛、僵尸) 展示一张照片，并对人 (牛、僵尸) 询问这张照片的上半部分和下半部分是否被交换。人（牛）会认真回答这样的问题； 而僵尸会随便按下两个按钮中的一个。人 (牛、僵尸) 会被询问数次, 如果正确的数量达到或超过 $75$ 个 ，则通向基地的门打开, 否则，通向死亡的门打开。

Heidi 正在组建能消灭僵尸的机器人军队, 她希望你能帮她完成机器人区分图像的功能。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF690E1/5049ba9bbfc4129520c0662372ea952b95839547.png)

这是测试所用的图片集的前两张，第一张的上下交换过，但第二张并没有。

## 说明/提示

[下载链接](http://assets.codeforces.com/files/690/easy_contestant_package.zip)

# AI分析结果

### 题目内容
# Photographs (I)

## 题目描述
Heidi组建的人牛联盟建造了一个防止僵尸攻击的基地，基地的入口有一个安全门，这个门执行一种测试，它会向进入的人（牛、僵尸）展示一张照片，并对人（牛、僵尸）询问这张照片的上半部分和下半部分是否被交换。人（牛）会认真回答这样的问题；而僵尸会随便按下两个按钮中的一个。人（牛、僵尸）会被询问数次，如果正确的数量达到或超过75个 ，则通向基地的门打开，否则，通向死亡的门打开。

Heidi正在组建能消灭僵尸的机器人军队，她希望你能帮她完成机器人区分图像的功能。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF690E1/5049ba9bbfc4129520c0662372ea952b95839547.png)

这是测试所用的图片集的前两张，第一张的上下交换过，但第二张并没有。

## 说明/提示
[下载链接](http://assets.codeforces.com/files/690/easy_contestant_package.zip)

### 算法分类
无算法分类

### 综合分析与结论
这几道题解思路相近，均基于正常图片颜色跨度小，交换上下部分后中间两行灰度差异会大于第一行与最后一行灰度差异这一特点来判断图片是否被交换。各题解主要差异在于代码实现细节和表述方式。

### 所选的题解
- **作者：Sine_Func（4星）**
  - **关键亮点**：思路清晰，代码简洁明了，使用 `#define int long long` 统一数据类型，利用 `abs` 函数计算灰度差值，逻辑直接易懂。
  - **重点代码**：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t, n, m, a[610][610], x, y;
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> t;
	while (t--) {
		cin >> n >> m;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				cin >> a[i][j];
			}
		}
		x = y = 0;
		for (int i = 1; i <= m; i++)
			x += abs(a[1][i] - a[n][i]);
		for (int i = 1; i <= m; i++)
			y += abs(a[n / 2][i] - a[n / 2 + 1][i]);
		if (x > y)cout << "NO\n";
		else cout << "YES\n";
	}
	return 0;
}
```
  - **核心实现思想**：读入图片灰度值，分别计算第一行与最后一行、中间两行的灰度差值总和 `x` 和 `y`，通过比较 `x` 和 `y` 的大小判断图片是否交换。

- **作者：loser_seele（4星）**
  - **关键亮点**：使用函数封装计算灰度差值平方和的操作，使代码结构更清晰，同样通过关闭流同步优化读入。
  - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int p[2020][2020];
int h,w;
int s(int x)
{
    return x*x;
}
int check(int r1,int r2)
{
    int res=0;
    for(int i=1;i<=w;i++)
    res+=s(p[r1][i]-p[r2][i]);
    return res;
}
signed main()
{
    ios::sync_with_stdio(0);
    int T;
    cin>>T;
    while(T--)
    {
        cin>>h>>w;
        for(int i=1;i<=h;i++)
        for(int j=1;j<=w;j++)
        cin>>p[i][j];
        if(check(1,h)<check(h/2,h/2+1))
        cout<<"YES"<<'\n';
        else
        cout<<"NO"<<'\n';
    }
}
```
  - **核心实现思想**：定义 `s` 函数计算平方，`check` 函数计算两行灰度差值平方和，通过比较第一行与最后一行、中间两行的灰度差值平方和判断图片是否交换。

### 最优关键思路或技巧
通过观察图片交换前后灰度值差异特征，选择比较图片第一行与最后一行、中间两行的灰度差异（差值或差值平方和）来判断图片是否被上下交换，利用题目允许的容错率简化判断逻辑。

### 可拓展之处
此类题目属于图像简单分析类型，类似套路可用于判断图像的左右翻转、旋转等简单变换，通过分析变换前后图像某些特征（如颜色、像素分布等）的变化来实现判断。

### 推荐洛谷题目
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：涉及枚举和简单的数学运算，与本题通过特定条件判断的思路有相似之处。
- [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：可使用动态规划或枚举方法解决，锻炼对条件判断和方案选择的能力。
- [P1423 小玉在游泳](https://www.luogu.com.cn/problem/P1423)：通过模拟和简单数学计算解决问题，与本题分析特征并判断的思维类似。 

---
处理用时：61.36秒