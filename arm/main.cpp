/*
 * @Author: w 2652289370@qq.com
 * @Date: 2023-04-07 16:35:04
 * @LastEditors: w 2652289370@qq.com
 * @LastEditTime: 2023-04-07 17:21:31
 * @FilePath: \arm\arm\main.cpp
 */
/*
 *                        _oo0oo_
 *                       o8888888o
 *                       88" . "88
 *                       (| -_- |)
 *                       0\  =  /0
 *                     ___/`---'\___
 *                   .' \\|     |// '.
 *                  / \\|||  :  |||// \
 *                 / _||||| -:- |||||- \
 *                |   | \\\  - /// |   |
 *                | \_|  ''\---/''  |_/ |
 *                \  .-\__  '-'  ___/-. /
 *              ___'. .'  /--.--\  `. .'___
 *           ."" '<  `.___\_<|>_/___.' >' "".
 *          | | :  `- \`.;`\ _ /`;.`/ - ` : | |
 *          \  \ `_.   \_ __\ /__ _/   .-` /  /
 *      =====`-.____`.___ \_____/___.-`___.-'=====
 *                        `=---='
 * 
 * 
 *      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 *            佛祖保佑     永不宕机     永无BUG
 */



#include <iostream>
#include "matrix.h"
#include "DH.h"

using namespace std;

 

int main() try
{
	/*Kinetic k;
	auto a = k.Fk(10.5, 1, 2.0, 0);
	cout << a << endl;*/

	/*DH* arms = new DH[6]();*/
	DH arms[6]{};
		
	arms[0] = { PI / 2, 0, 0.43, 0 };
	arms[1] = { 0, 0, 0.43, 0 };
	arms[2] = { 0, 0, 0.43, 0 };
	arms[3] = { PI / 2, 0, 0.43, 0 };
	arms[4] = {-PI / 2, 0, 0.43, 0 };
	arms[5] = { 0, 0, 0.43, 0 };
	
	Kinetic k(arms, arraysize(arms));

}	
catch (const char* msg)
{
	cout << msg << endl;
}