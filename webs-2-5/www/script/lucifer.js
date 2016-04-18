/*
function removeDiv(_id)
{
//	alert(_id);
	var _div = document.getElementById(_id);
	var divChatBG = document.getElementById("idChatBG");
	divChatBG.removeChild(_div);	
}
*/

function createChatASms(_id, _msg)
{
	var divChat = document.createElement("div");  
	divChat.className = "chatA";
	divChat.id = _id;
	
	var divBlank = document.createElement("div"); 
	divBlank.className = "blankA";		

	var divTrip = document.createElement("div");
	divTrip.className = "tripA";
	divTrip.innerHTML = "<img src=\"images/chatATrip.png\"></img>";
	
	var divSms = document.createElement("div"); 
	divSms.className = "smsA";
	divSms.innerHTML = _msg;
	
	document.getElementById("idChatBG").appendChild(divChat);
	
	divChat.appendChild(divBlank);	
	divChat.appendChild(divTrip);
	divChat.appendChild(divSms);	
		
}
function createChatBSms(_id, _msg)
{
	var divChat = document.createElement("div");  
	divChat.className = "chatB";
	divChat.id = _id;

	var divBlank = document.createElement("div"); 
	divBlank.className = "blankB";	

	var divTrip = document.createElement("div");
	divTrip.className = "tripB"; 
	divTrip.innerHTML = "<img src=\"images/chatBTrip.png\"></img>";
	
	var divSms = document.createElement("div"); 
	divSms.className = "smsB";
	divSms.innerHTML = _msg;
	
	document.getElementById("idChatBG").appendChild(divChat);

	divChat.appendChild(divBlank);
	divChat.appendChild(divTrip);		
	divChat.appendChild(divSms);

}

function createRow(_rid, _objRow)
{
	var _divRow = document.createElement("div");  
	_divRow.className = "smsRow";
	_divRow.id = _rid;	
	_divRow.onclick = onClickSms;
	
	var _div1st = document.createElement("div"); 

	var _div2nd = document.createElement("div"); 
	_div2nd.className = "smsMsg";
	_div2nd.id = "idMsg" + _rid;
	_div2nd.innerHTML = _objRow.Msg;
	
	
	var _spanNo   = document.createElement("span"); 
	_spanNo.className = "smsNo";
	_spanNo.id = "idNo" + _rid;
	_spanNo.innerHTML = _objRow.No;	
	
	var _spanTime = document.createElement("span"); 
	_spanTime.className = "smsTime";
	_spanTime.id = "idTime" + _rid;	
	_spanTime.innerHTML = _objRow.Date;	
	
	_divRow.appendChild(_div1st);	
	_divRow.appendChild(_div2nd);	

	_div1st.appendChild(_spanNo);
	_div1st.appendChild(_spanTime);		
	
	document.getElementById("idSmsBG").appendChild(_divRow);	

}
var g_last_div = null;

function onClickSms(eventTag)
{
	var event ;
	if( eventTag != null)
	{
		event = eventTag;
	}
	else
	{
		event = window.event;
	}
	
	var _div;
	if(event.currentTarget == null)
	{
		_div = event.srcElement;
	}
	else
	{
		_div = event.currentTarget;
	}
	if(_div == null)
	{
		alert("浏览器不支持该功能，请升级浏览器！");
	}
	
	setSelected(_div, 1);
		
	if(g_last_div != null && _div != g_last_div)
	{
		setSelected(g_last_div, 0);
	}
	g_last_div = _div;
}

function setSelected(_div, _selected)
{
	if(_selected == 0)
	{
		_div.style.background = "white";
		
		var _spanNo = document.getElementById("idNo" + _div.id);
		_spanNo.style.color = "black";
		
		var _spanTime = document.getElementById("idTime" + _div.id);
		_spanTime.style.color = "black";
		
		var _divMsg = document.getElementById("idMsg" + _div.id);
		_divMsg.style.color = "#808080";		
	}
	else
	{
		_div.style.background = "black";
		
		var _spanNo = document.getElementById("idNo" + _div.id);
		_spanNo.style.color = "white";
		
		var _spanTime = document.getElementById("idTime" + _div.id);
		_spanTime.style.color = "white";
		
		var _divMsg = document.getElementById("idMsg" + _div.id);
		_divMsg.style.color = "#A0A0A0";
		
	}
}
