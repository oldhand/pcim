========================================================================
    静态库：rest 项目概述
========================================================================

应用程序向导已为您创建了此 rest 库项目。

本文件概要介绍组成 rest 应用程序的每个文件的内容。


rest.vcxproj
    这是使用应用程序向导生成的 VC++ 项目的主项目文件，其中包含生成该文件的 Visual C++ 的版本信息，以及有关使用应用程序向导选择的平台、配置和项目功能的信息。

rest.vcxproj.filters
    这是使用“应用程序向导”生成的 VC++ 项目筛选器文件。它包含有关项目文件与筛选器之间的关联信息。在 IDE 中，通过这种关联，在特定节点下以分组形式显示具有相似扩展名的文件。例如，“.cpp”文件与“源文件”筛选器关联。


/////////////////////////////////////////////////////////////////////////////

StdAfx.h, StdAfx.cpp
    这些文件用于生成名为 rest.pch 的预编译头 (PCH) 文件和名为 StdAfx.obj 的预编译类型文件。

/////////////////////////////////////////////////////////////////////////////
其他注释:

应用程序向导使用“TODO:”注释来指示应添加或自定义的源代码部分。

/////////////////////////////////////////////////////////////////////////////


/*try {
	Content content = XN_Content::load("13878");
	}
	catch (std::exception& errorMsg) {
	printf_s("_______XN_Content::load();__________%s___________\n", errorMsg.what());
	}
	try {
		std::list<Content> lists = XN_Content::loadMany({ 13878, 1332 });
	}
	catch (std::exception& errorMsg) {
		printf_s("_______XN_Content::loadMany();__________%s___________\n", errorMsg.what());
	}
	try {
		Content newcontent = XN_Content::create("im_likes", "", false);
		std::string tmp = "中华人民共和国"; 
		tmp = nbase::strings::gbk_to_utf8(tmp);
		newcontent.my["supplierid"] = "admin";
		newcontent.my["deleted"] = "0";
		newcontent.my["aa"] = tmp;
		newcontent.my["bb"] = "0123123123";
		newcontent.save("im_likes,im_likes_123");
		newcontent.my["cc"] = "0123123123";
		newcontent.my["dd"] = "asdasdasdasdad";
		newcontent.save("im_likes,im_likes_123");

		newcontent.erase("im_likes,im_likes_123");
		newcontent.erase("im_likes,im_likes_123");
	}
	catch (std::exception& errorMsg) {
		printf_s("________________%s___________\n", errorMsg.what());
	}*/
