#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <regex>
#include <codecvt>
#include "head.h"
using namespace std;

wstring addr;	//地址变量
wstring direct_city[4] = { L"北京市",L"上海市",L"天津市",L"重庆市" };//直辖市
wstring direct_cities[4][40] = {
	L"朝阳区",L"海淀区",L"通州区",L"房山区",L"丰台区",L"昌平区",L"大兴区",L"顺义区",L"西城区",L"延庆县",L"石景山区",L"宣武区",L"怀柔区",L"崇文区",L"密云县",L"东城区",L"门头沟区",L"平谷区",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",
		L"松江区",L"宝山区",L"金山区",L"嘉定区",L"南汇区",L"青浦区",L"浦东新区",L"奉贤区",L"闵行区",L"徐汇区",L"静安区",L"黄浦区",L"普陀区",L"杨浦区",L"虹口区",L"闸北区",L"长宁区",L"崇明县",L"卢湾区",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",
		L"和平区",L"北辰区",L"河北区",L"河西区",L"西青区",L"津南区",L"东丽区",L"武清区",L"宝坻区",L"红桥区",L"大港区",L" 汉沽区",L"静海县",L"宁河县",L"塘沽区",L"蓟县",L"南开区",L"河东区",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",
		L"江北区",L"渝北区",L"沙坪坝区",L"九龙坡区",L"万州区",L"永川市",L"南岸区",L"酉阳县",L"北碚区",L"涪陵区",L"秀山县",L"巴南区",L"渝中区",L"石柱县",L"忠县",L"合川市",L"大渡口区",L"开县",L"长寿区",L"荣昌县",L"云阳县",L"梁平县",L"潼南县",L"江津市",L"彭水县",L"璧山县",L"綦江县",L"大足县",L"黔江区",L"巫溪县",
			L"巫山县", L"垫江县", L"丰都县", L"武隆县", L"万盛区", L"铜梁县", L"南川市", L"奉节县", L"双桥区", L"城口县" };
wstring provs[23] = { L"河北省",L"山西省",L"辽宁省",L"吉林省",L"黑龙江省",L"江苏省",L"浙江省",L"安徽省",L"福建省",L"江西省",L"山东省",L"河南省",L"湖北省",L"湖南省",L"广东省",L"海南省",L"四川省",L"贵州省",L"云南省",L"陕西省",L"甘肃省",L"青海省",L"台湾省" };									//全国各省
wstring cities[23][30] =
{ L"石家庄市",L"唐山市",L"保定市",L"邯郸市",L"邢台市",L"河北区",L"沧州市",L"秦皇岛市",L"张家口市",L"衡水市",L"廊坊市",L"承德市",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",
L"太原市",L"大同市",L"运城市",L"长治市",L"晋城市",L"忻州市",L"临汾市",L"吕梁市",L"晋中市",L"阳泉市",L"朔州市",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",
L"大连市",L"沈阳市",L"丹东市",L"辽阳市",L"葫芦岛市",L"锦州市",L"朝阳市",L"营口市",L"鞍山市",L"抚顺市",L"阜新市",L"本溪市",L"盘锦市",L"铁岭市",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",
L"吉林市",L"长春市",L"白山市",L"白城市",L"延边州",L"松原市",L"辽源市",L"通化市",L"四平市",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",
L"齐齐哈尔市",L"哈尔滨市",L"大庆市",L"佳木斯市",L"双鸭山市",L"牡丹江市",L"鸡西市",L"黑河市",L"绥化市",L"鹤岗市",L"伊春市",L"大兴安岭地区",L"七台河市",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",
L"苏州市",L"徐州市",L"盐城市",L"无锡市",L"南京市",L"南通市",L"连云港市",L"常州市",L"扬州市",L"镇江市",L"淮安市",L"泰州市",L"宿迁市",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",
L"温州市",L"宁波市",L"杭州市",L"台州市",L"嘉兴市",L"金华市",L"湖州市",L"绍兴市",L"舟山市",L"丽水市",L"衢州市",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",
L"芜湖市",L"合肥市",L"六安市",L"宿州市",L"阜阳市",L"安庆市",L"马鞍山市",L"蚌埠市",L"淮北市",L"淮南市",L"宣城市",L"黄山市",L"铜陵市",L"亳州市",L"池州市",L"巢湖市",L"滁州市",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",
L"漳州市",L"泉州市",L"厦门市",L"福州市",L"莆田市",L"宁德市",L"三明市",L"南平市",L"龙岩市",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",
L"南昌市",L"赣州市",L"上饶市",L"吉安市",L"九江市",L"新余市",L"抚州市",L"宜春市",L"景德镇市",L"萍乡市",L"鹰潭市",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",
L"济南市",L"青岛市",L"临沂市",L"济宁市",L"菏泽市",L"烟台市",L"泰安市",L"淄博市",L"潍坊市",L"日照市",L"威海市",L"滨州市",L"东营市",L"聊城市",L"德州市",L"莱芜市",L"枣庄市",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",
L"郑州市",L"南阳市",L"新乡市",L"安阳市",L"洛阳市",L"信阳市",L"平顶山市",L"周口市",L"商丘市",L"开封市",L"焦作市",L"驻马店市",L"濮阳市",L"三门峡市",L"漯河市",L"许昌市",L"鹤壁市",L"济源市",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",
L"武汉市",L"宜昌市",L"襄樊市",L"荆州市",L"恩施州",L"孝感市",L"黄冈市",L"十堰市",L"咸宁市",L"黄石市",L"仙桃市",L"随州市",L"天门市",L"荆门市",L"潜江市",L"鄂州市",L"神农架林区",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",
L"长沙市",L"邵阳市",L"常德市",L"衡阳市",L"株洲市",L"湘潭市",L"永州市",L"岳阳市",L"怀化市",L"郴州市",L"娄底市",L"益阳市",L"张家界市",L"湘西州",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",""
L"东莞市",L"广州市",L"中山市",L"深圳市",L"惠州市",L"江门市",L"珠海市",L"汕头市",L"佛山市",L"湛江市",L"河源市",L"肇庆市",L"潮州市",L"清远市",L"韶关市",L"揭阳市",L"阳江市",L"云浮市",L"茂名市",L"梅州市",L"汕尾市",L"",L"",L"",L"",L"",L"",L"",L"",L"",
L"三亚市",L"海口市",L"琼海市",L"文昌市",L"东方市",L"昌江县",L"陵水县",L"乐东县",L"五指山市",L"保亭县",L"澄迈县",L"万宁市",L"儋州市",L"临高县",L"白沙县",L"定安县",L"琼中县",L"屯昌县",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",
L"成都市",L"绵阳市",L"广元市",L"达州市",L"南充市",L"德阳市",L"广安市",L"阿坝州",L"巴中市",L"遂宁市",L"内江市",L"凉山州",L"攀枝花市",L"乐山市",L"自贡市",L"泸州市",L"雅安市",L"宜宾市",L"资阳市",L"眉山市",L"甘孜州",L"",L"",L"",L"",L"",L"",L"",L"",L"",
L"贵阳市",L"黔东南州",L"黔南州",L"遵义市",L"黔西南州",L"毕节地区",L"铜仁地区",L"安顺市",L"六盘水市",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",
L"昆明市",L"红河州",L"大理州",L"文山州",L"德宏州",L"曲靖市",L"昭通市",L"楚雄州",L"保山市",L"玉溪市",L"丽江地区",L"临沧地区",L"思茅地区",L"西双版纳州",L"怒江州",L"迪庆州",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",
L"西安市",L"咸阳市",L"宝鸡市",L"汉中市",L"渭南市",L"安康市",L"榆林市",L"商洛市",L"延安市",L"铜川市",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",
L"兰州市",L"天水市",L"庆阳市",L"武威市",L"酒泉市",L"张掖市",L"陇南地区",L"白银市",L"定西地区",L"平凉市",L"嘉峪关市",L"临夏回族自治州",L"金昌市",L"甘南州",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",
L"西宁市",L"海西州",L"海东地区",L"海北州",L"果洛州",L"玉树州",L"黄南藏族自治州",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",
L"台北市",L"高雄市",L"台中市",L"新竹市",L"基隆市",L"台南市",L"嘉义市",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L""
};
wstring zzq[5] = { L"广西壮族自治区",L"内蒙古自治区",L"新疆维吾尔自治区",L"宁夏回族自治区",L"西藏自治区" };//自治区
wstring zzq_cities[5][18] = {
	L"贵港市",L"玉林市",L"北海市",L"南宁市",L"柳州市",L"桂林市",L"梧州市",L"钦州市",L"来宾市",L"河池市",L"百色市",L"贺州市",L"崇左市",L"防城港市",L"",L"",L"",L"",
L"赤峰市",L"包头市",L"通辽市",L"呼和浩特市",L"乌海市",L"鄂尔多斯市",L"呼伦贝尔市",L"兴安盟",L"巴彦淖尔盟",L"乌兰察布盟",L"锡林郭勒盟",L"阿拉善盟",L"",L"",L"",L"",L"",L"",
L"乌鲁木齐市",L"伊犁州",L"昌吉州",L"石河子市",L"哈密地区",L"阿克苏地区",L"巴音郭楞州",L"喀什地区",L"塔城地区",L"克拉玛依市",L"和田地区",L"阿勒泰州",L"吐鲁番地区",L"阿拉尔市",L"博尔塔拉州",L"五家渠市",L"克孜勒苏州",L"图木舒克市",
L"银川市",L"吴忠市",L"中卫市",L"石嘴山市",L"固原市",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",L"",
L"拉萨市",L"山南地区",L"林芝地区",L"日喀则地区",L"阿里地区",L"昌都地区",L"那曲地区",L"",L"",L"",L"",L"",L"",L"",L"",L"",L""
};//自治区城市

wstring type_seperate()			//地址类型解析
{
	wstring type = addr.substr(0, addr.find(L"!") + 1);
	addr = addr.erase(0, addr.find(L"!")+1);
	return type;
}

wstring name_seperate() //解析姓名
{
	int flag = addr.find(L',');
	wstring name = addr.substr(0, flag);
	addr.erase(0, flag);	//解析出姓名后将姓名擦去
	addr.erase(addr.find(L"."), 1); //擦去 '.'
	addr.erase(addr.find(L","), 1); //擦去 ','
	return name;
}

wstring Tel_num_analysis()//提取11位电话号码
{
	smatch t;
	regex r("\\d{11}");
	string s = UnicodeToUTF8(addr);
	regex_search(s, t, r);
	wstring Tel_number = UTF8ToUnicode(t.str());
	s = regex_replace(s, r, "");
	addr = UTF8ToUnicode(s);

	return Tel_number;
};

class Five_addr_analysis		//五位地址解析
{
public:
	wstring name, tel_number, pro, Cities, country, town, detail_addr;
	int prov_tag;	//省份对应下标
	Five_addr_analysis(wstring Name, wstring Tel_num)
	{
		prov_tag = 0;
		name = Name;
		tel_number = Tel_num;
		pro = Cities = country = town = detail_addr = L"";
	}
	void provs_seperate()//解析省
	{
		int flag;
		for (int i = 0; i < 23; i++)
		{
			/*地址中带"省"*/
			wstring temp = provs[i].substr(0, provs[i].size() - 1); //提取省份名称，例如：福建
			if ((flag = addr.find(provs[i])) != -1)
			{
				pro = provs[i];
				prov_tag = i;
				addr.erase(flag, provs[i].size()); //擦去“省”
				return;
			}
			/*地址中不带"省"的省*/
			else if ((flag = addr.find(temp)) != -1)
			{
				pro = provs[i];
				prov_tag = i;
				addr.erase(flag, temp.size()); //擦去“省”
				return;
			}

			/*直辖市、自治区前四个*/
			if (i < 4)
			{
				/*直辖市*/
				if ((flag = addr.find(direct_city[i])) != -1)
				{
					pro = direct_city[i];
					addr.erase(flag, direct_city[i].size());
					prov_tag = i + 23;//区分直辖市
					return;
				}
				temp = direct_city[i].substr(0, direct_city[i].size() - 1);//提取直辖市名称,例如：北京
				if ((flag = addr.find(temp)) != -1)
				{
					pro = direct_city[i];
					addr.erase(flag, temp.size());
					prov_tag = i + 23;//区分直辖市
					return;
				}

				/*自治区*/
				if ((flag = addr.find(zzq[i])) != -1)
				{
					pro = zzq[i];
					addr.erase(flag, zzq[i].size());
					prov_tag = i + 27;//区分自治区
					return;
				}
				temp = zzq[i].substr(0, zzq[i].size() - 3);//提取自治区名字如内蒙古
				if ((flag = addr.find(temp)) != -1)
				{
					pro = zzq[i];
					addr.erase(flag, temp.size());
					prov_tag = i + 27;//区分直辖市
					return;
				}
			}

			/*自治区*/
			if (i == 4)
			{
				if ((flag = addr.find(zzq[i])) != -1)
				{
					pro = zzq[i];
					addr.erase(flag, zzq[i].size());
					prov_tag = i + 27;//区分自治区
					return;
				}
				temp = zzq[i].substr(0, zzq[i].size() - 3);//提取自治区名字西藏
				if ((flag = addr.find(temp)) != -1)
				{
					pro = zzq[i];
					addr.erase(flag, temp.size());
					prov_tag = i + 27;//区分直辖市
					return;
				}
			}
		}
	}
	void cities_seperate()//解析市
	{
		int flag;
		if (prov_tag < 23) //一般城市
		{
			for (int i = 0; i < 30; i++)
			{
				if ((flag = addr.find(cities[prov_tag][i])) != -1)
				{
					Cities = cities[prov_tag][i];
					addr.erase(flag, cities[prov_tag][i].size()); //擦去“市”
					return;
				}
				/*地址中不带"市"*/
				else
				{
					wstring temp = cities[prov_tag][i].substr(0, cities[prov_tag][i].size() - 1);
					if ((flag = addr.find(temp)) != -1)
					{
						Cities = cities[prov_tag][i];
						addr.erase(flag, temp.size()); //擦去“市”
						return;
					}
				}
			}
		}
		else if (prov_tag < 27)//直辖市下的城市
		{
			prov_tag -= 23;
			for (int j = 0; j < 40; j++)
			{
				if ((flag = addr.find(direct_cities[prov_tag][j])) != -1)
				{
					Cities = direct_cities[prov_tag][j];
					addr.erase(flag, Cities.size());
					return;
				}
				wstring t = direct_cities[prov_tag][j].substr(0, direct_cities[prov_tag][j].size() - 1);
				if ((flag = addr.find(t)) != -1)
				{
					Cities = direct_cities[prov_tag][j];
					addr.erase(flag, t.size());
					return;
				}
			}
		}
		else//自治区下的城市
		{
			prov_tag -= 27;
			for (int j = 0; j < 18; j++)
			{
				if ((flag = addr.find(zzq_cities[prov_tag][j])) != -1)
				{
					Cities = zzq_cities[prov_tag][j];
					addr.erase(flag, Cities.size());
					return;
				}
				wstring t = zzq_cities[prov_tag][j].substr(0, zzq_cities[prov_tag][j].size() - 1);
				if ((flag = addr.find(t)) != -1)
				{
					Cities = zzq_cities[prov_tag][j];
					addr.erase(flag, t.size());
					return;
				}
				t = zzq_cities[prov_tag][j].substr(0, zzq_cities[prov_tag][j].size() - 4);
				if ((flag = addr.find(t)) != -1)
				{
					Cities = zzq_cities[prov_tag][j];
					addr.erase(flag, t.size());
					return;
				}
			}
		}
	}
	void counties_seperate()//解析县/区/县级市
	{
		string s = UnicodeToUTF8(addr);
		regex r(".*?(区|县|市)");
		smatch Country;
		regex_search(s, Country, r);//解析到县/区/县级市
		string country1;
		country1 += Country.str();
		country = UTF8ToUnicode(country1);
		s = regex_replace(s, r, "");
		addr = UTF8ToUnicode(s);
	}
	void towns_seperate()//解析街道/镇/乡
	{
		string s = UnicodeToUTF8(addr);
		regex r(".+((街道)|镇|乡)");
		smatch Town;
		regex_search(s, Town, r);//解析到街道/乡/镇
		town = UTF8ToUnicode(Town.str());		//保存到town中
		s = regex_replace(s, r, "");
		addr = UTF8ToUnicode(s);
		return;
	}
	void detail_seperate()//解析 详细地址
	{
		detail_addr = addr;
	}
	void info_collect()//地址解析函数
	{
		provs_seperate();
		cities_seperate();
		counties_seperate();
		towns_seperate();
		detail_seperate();
	}
	wstring print_info()	//五级地址格式输出
	{
		wstring address = L"{\"姓名\":\"" + name + L"\",\"手机\":\"" + tel_number + L"\",\"地址\":[" + L"\"" + pro + L"\",\"" + Cities + L"\",\""
			+ country + L"\",\"" + town + L"\",\"" + detail_addr + L"\"]}";
		//cout << address << endl;
		return address;
	}
};

class Seven_addr_analysis :public Five_addr_analysis
{
public:
	wstring road, gate_num;
	Seven_addr_analysis(wstring name, wstring tel_number) :Five_addr_analysis(name, tel_number) { road = gate_num = L""; }
	void road_seperate()//解析路
	{
		string s = UnicodeToUTF8(addr);
		regex r(".+(路|街|巷|(胡同)|里)");
		smatch Road;
		regex_search(s, Road, r);
		road = UTF8ToUnicode(Road.str());
		addr = UTF8ToUnicode(regex_replace(s, r, ""));
		return;
	}
	void gate_number()//解析门牌号
	{
		string s = UnicodeToUTF8(addr);
		regex r(".+(号)");
		smatch gate;
		regex_search(s, gate, r);
		gate_num = UTF8ToUnicode(gate.str());
		addr = UTF8ToUnicode(regex_replace(s, r, ""));
		return;
	}
	void provs_seperate()	//解析省
	{
		int flag;
		for (int i = 0; i < 23; i++)
		{
			/*地址中带"省"*/
			wstring temp = provs[i].substr(0, provs[i].size() - 1); //提取省份名称，例如：福建
			if ((flag = addr.find(provs[i])) != -1)
			{
				pro = provs[i];
				prov_tag = i;
				addr.erase(flag, provs[i].size()); //擦去“省”
				return;
			}
			/*地址中不带"省"的省*/
			else if ((flag = addr.find(temp)) != -1)
			{
				pro = provs[i];
				prov_tag = i;
				addr.erase(flag, temp.size()); //擦去“省”
				return;
			}
			/*直辖市*/
			if (i < 4)
			{
				//temp = direct_city[i].substr(0, direct_city[i].size() - 2);//匹配直辖市全称
				if ((flag = addr.find(direct_city[i])) != -1)
				{
					pro = direct_city[i];
					addr.erase(flag, direct_city[i].size());
					prov_tag = i + 23;//区分直辖市
					return;
				}
			}
		}
	}
	void info_collect()//提取地图信息
	{
		provs_seperate();
		cities_seperate();
		counties_seperate();
		towns_seperate();
		road_seperate();
		gate_number();
		detail_seperate();
	}
	wstring print_info()//七级地址格式输出
	{
		wstring address = L"{\"姓名\":\"" + name + L"\",\"手机\":\"" + tel_number + L"\",\"地址\":[" + L"\"" + pro + L"\",\"" + Cities + L"\",\""
			+ country + L"\",\"" + town + L"\",\"" + road + L"\",\"" + gate_num + L"\",\"" + detail_addr + L"\"]}";
		//cout << address << endl;
		return address;
	}
};


int main(int argc, char **argv)
{
	ifstream input;
	ofstream output;
	input.open(argv[1]);
	output.open(argv[2]);
	/*ifstream input;
	ofstream output;
	input.open("E:\\SoftwareTest-1.0.0\\dl\\lxc\\input.txt");
	output.open("E:\\SoftwareTest-1.0.0\\dl\\lxc\\output.txt");*/
	vector<string> address;
	int count = 0;
	string s;
	output << "[" << endl;
	while (getline(input, s))
	{
		address.push_back(s);
		count++;
	}

	for (int i = 0; i < count; i++)
	{
		addr = UTF8ToUnicode( address[i]);
		wstring type = type_seperate();
		wstring name = name_seperate();
		wstring tel_number = Tel_num_analysis();
		wstring t1 = L"1!",t2 = L"2!";
		if (type.find==t1)
		{
			Five_addr_analysis add_analysis(name, tel_number); //创建五级地址对象
			add_analysis.info_collect();
			wstring info = add_analysis.print_info();
			//写入文件
			if (i != count - 1)
			{
				info += L",";
				string inf = UnicodeToUTF8(info);
				//cout << inf << endl;
				output << inf << endl;
			}
			else
			{
				string inf = UnicodeToUTF8(info);
				//cout << inf << endl;
				output << inf << endl;
			}
		}
		else if (type.find==t2)
		{
			Seven_addr_analysis add_analysis(name, tel_number);//创建七级地址对象
			add_analysis.info_collect();
			wstring info = add_analysis.print_info();
			//写入文件
			if (i != count - 1)
			{
				info += L",";
				string inf = UnicodeToUTF8(info);
				//cout << inf<<endl;
				output << inf << endl;
			}
			else
			{
				string inf = UnicodeToUTF8(info);
				//cout << inf<<endl;
				output << inf << endl;
			}
		}
		/*else if(type == L"3!")
		{
			output << "Cant' deal with case 3!" << endl;
		}
		else
		{
			output << "Type Wrong!" << endl;
		}*/
	}
	output << "]" << endl;
	input.close();
	output.close();


	/*fstream f("F:\\VS project\\test_date.txt");
	ofstream o("F:\\VS project\\test_result_date.txt");
	string s;
	while (getline(f, s))
	{
		addr = UTF8ToUnicode(s);
		//addr = L"1!小兲,西藏自治区拉萨市城关区中路35号布达拉宫内12345678910.";
		wstring type = type_seperate();
		wstring name = name_seperate();
		wstring tel_number = Tel_num_analysis();

		if (type == L"1!")
		{
			Five_addr_analysis add_analysis(name, tel_number); //创建五级地址对象
			add_analysis.info_collect();
			add_analysis.print_info();
		}
		else if (type == L"2!")
		{
			Seven_addr_analysis add_analysis(name, tel_number);//创建七级地址对象
			add_analysis.info_collect();
			add_analysis.print_info();
		}

	}
	f.close();
	system("pause");*/
	
	return 0;
}
