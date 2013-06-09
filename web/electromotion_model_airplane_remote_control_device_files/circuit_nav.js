function $$(a){return document.getElementById(a);}
function swTags(a){
	var tmp=a.id.split("_");
	var sid=tmp[0];
	var snum=tmp[1];
	var i=1;
	var tabs=sid+"_";
	var tags=sid+"_con_";
	while($$(tabs+i)){
		if($$(tabs+i)!=a){
			$$(tabs+i).className="Datasheet";
		}
		i++;
	}
	var j=1;
	while($$(tags+j)){
		if(snum==j){
			$$(tags+j).className="submitDis";
		}else{
			$$(tags+j).className="submitUndis";
		}
		j++;
	}
	a.className="Suppliers";
	tmp=sid=snum=i=j=tabs=tags=null;
}




function CheckSuppliersSearch(form){
	var keyword = form.keyword.value;
	if(keyword == "" ){
	   alert("Please input part number!");
	   form.keyword.focus();
	   return false;
	 }
	if(keyword.length<4){
	  alert("Part number must be in more than 4 digits and/or letters.");
	  form.keyword.focus();
	  return false;
	 }
	 return true;
}
 
function CheckDataSheetSearch(form){
	var keyword = form.keyword.value;
	if(keyword == "" ){
	   alert("Please input part number!");
	   form.keyword.focus();
	   return false;
	 }
	if(keyword.length<3){
	  alert("Part number must be in more than 3 digits and/or letters.");
	  form.keyword.focus();
	  return false;
	 }
	 return true;
}





function validateEmailgo(obj){
	var str = obj.value;
	str = quanjiao2Banjiaogo(str);
	obj.value = str;
	var patn = /^[_a-zA-Z0-9\-]+(\.[_a-zA-Z0-9\-]*)*@[a-zA-Z0-9\-]+([\.][a-zA-Z0-9\- ]+)+$/;
	if(patn.test(str)){	
		return true;
	}else{
		return false; //incorrect format
	}
}
function quanjiao2Banjiaogo(str) {
	var i;
	var result = '';
	for (i = 0; i < str.length; i++) {
		code = str.charCodeAt(i);
		if (code >= 65281 && code < 65373) {
			result += String.fromCharCode(str.charCodeAt(i) - 65248);
		}
		else {
			result += str.charAt(i);
		}
	}
	return result;
}


	function ChecksendGo(form){	
		  if(form.partnumber.value==""){
		      alert("Please input Part No..");
			  form.partnumber.focus();
			  return false;			  
		  }
		  if(form.qty.value==""){
		      alert("Please input the quantity.");
			  form.qty.focus();
			  return false;			  
		  }
		 
		if(!validateEmailgo(form.mail)){		  
		     alert("Pleast enter your valid Email address.");
			 form.mail.focus();
			 return false;
		  }
		return true;
	   }












 
function Nav(){
html = '  <div style="margin: 0px; padding: 0px; position: absolute; top: 0px; left: 0px; width: 100%;">';
html += '    <div id="IC_Indextop">';
html += '      <div class="signIn">HI,Welcome to SeekIC <a href="/member/login.html" rel="nofollow">Sign In</a> | <a href="/member/reg.html" rel="nofollow">Join Free</a> |<a href="/member/getpsw.html" rel="nofollow"> Forgot Password</a></div>';
html += '      <div class="top">';
html += '        <div class="Logo"><a href="/" rel="nofollow"><img src="/images/logo.gif" alt="SeekIC Index" border="0"></a></div>';
html += '        <div class="Search">';
html += '          <div class="select_Type">';
html += '            <div class="Suppliers" id="tabs7_1" onclick="swTags(this)">Suppliers</div>';
html += '            <div class="Datasheet" id="tabs7_2" onclick="swTags(this)">DataSheet</div>';
html += '          </div>';
html += '          <div class="submitDis" id="tabs7_con_1">';
html += '            <form name="SuppliersSearch" method="get" action="/buyer/search.html" onsubmit="return CheckSuppliersSearch(this)">';
html += '              <div class="Input">';
html += '                <input name="keyword" class="keyword" id="keyword" type="text">';
html += '              </div>';
html += '              <div class="Exact_Match">';
html += '                <input name="searchtype" id="searchtype" value="2" type="checkbox">Exact Match</div>';
html += '              <div class="Submit_Search">';
html += '                <input src="/images/search.gif" value="Search" type="image">';
html += '              </div>';
html += '            </form>';
html += '          </div>';
html += '          <div class="submitUndis" id="tabs7_con_2">';
html += '            <form name="DataSheetSearch" method="get" action="/pdf/" onsubmit="return CheckDataSheetSearch(this)">';
html += '              <div class="DataInput">';
html += '                <input name="keyword" class="Datakeyword" id="keyword" type="text">';
html += '              </div>';
html += '              <div class="DataSubmit_Search">';
html += '                <input src="/images/search.gif" value="Search" type="image">';
html += '              </div>';
html += '            </form>';
html += '          </div>';
html += '        </div>';
html += '        <div class="Urgent_Purchase"><a href="http://im.seekic.com/service/link1.asp?ver=1&siteurl=eccec82316d2857b9f2cea3e27710b27&portId=1&status=1&itemId=1&comId=1" target="_blank" rel="nofollow"><img src="/images/IC_03.gif" alt="Urgent Purchase" border="0"></a></div>';
html += '      </div>';
html += '    </div>';
html += '    <div id="IC_Nav">';
html += '      <div class="Nav_Index">';
html += '        <div class="Home"><a href="/" title="SeekIC Index" rel="nofollow">Home</a></div>';
html += '        <div class="ForBuyer"><a href="/buyer/" title="For Buyer" rel="nofollow" >For Buyer</a></div>';
html += '        <div class="ForSeller"><a href="/seller/" title="For Seller" rel="nofollow">For Seller</a></div>';
html += '        <div class="CircuitDiagram_select"><a href="/circuit_diagram/" title="Circuit Diagram" rel="nofollow">Circuit Diagram</a></div>';
html += '        <div class="Manufacturer"><a href="/Manufacturer/" title="Manufacturer" rel="nofollow">Manufacturer</a></div>';
html += '        <div class="MyAccount"><a href="/product/" title="Product Center" >Product</a></div>';
html += '        <div class="LEDPurchase"><a href="http://member.seekic.com/" title="IC Suppliers" target="_blank">IC Suppliers</a></div>';
html += '        <div class="Blog"><a href="/blog/" title="Blog Center" target="_blank" rel="nofollow">Blog</a></div>';
html += '      </div>';
html += '    </div>';


html += '<div class="quote_bg">';
html += '  <div id="Quote">';
html += '  <form id="form1" name="form1" method="post" action="/seller/busyinfo.html" onSubmit="return ChecksendGo(this)" style="margin:0px; padding:0px;">';
html += '      <ul>';
html += '        <li class="quote">';
html += '          <a href="/seller/busyinfo.html" rel="nofollow" target="_blank"><img src="/images/ico_quote_08.gif"  onmouseover=this.src="/images/ico_quote_07.gif" onmouseout=this.src="/images/ico_quote_08.gif" alt="Get a Quote/Urgent Purchase"/></a>';
html += '        </li>';
html += '        <li class="part"> <b>Part Number</b>';
html += '          <input name="partnumber" type="text" class="partnumber" id="partnumber"  align="absmiddle"/>';
html += '        </li>';
html += '        <li class="qty"> <b>Qty </b>';
html += '          <input name="qty" type="text" class="Qty" id="qty"  align="absmiddle" />';
html += '        </li>';
html += '        <li class="email"> <b>Email </b>';
html += '          <input name="mail" type="text" class="email" id="mail"  align="absmiddle" />';
html += '        </li>';
html += '        <li class="go">';
html += '          <input type="image" src="/images/ico_quote_09.gif" />';
html += '        </li>';
html += '      </ul>';
html += '	  </form>';
html += '      <p>Response in 12 hours</p>';
html += '      <div class="clear"></div>';
html += '    </div>';
html += '</div>';


html += '  </div>';



html += '<div id="copyright">';
html += '	<div class="bg"></div>';
html += '	<div class="content">';
html += '		<div class="CopyAllRight-Nav">';
html += '			<a href="/about/" rel="nofollow">About SeekIC</a> | <a href="/about/Services.html" rel="nofollow">Services</a> | <a href="/about/Payment.html" rel="nofollow">Payment</a> | <a href="/about/advertisements.html" rel="nofollow">Advertisements service</a> | <a href="/about/Contact.html" rel="nofollow">Contact Us</a> | <a href="/about/Links.html" rel="nofollow">Links</a>';
html += '		  <p>&copy; 2008-2012 SeekIC.com Corp.All Rights Reserved.</p>';
html += '	  </div>';
html += '		<div class="CopySeekIC"><a href="/about/" target="_blank" rel="nofollow"><img src="/images/CopyLogo.gif" alt="About SeekIC" width="120" height="49" border="0" /></a></div>';
html += '	</div>';
html += '</div>';

return html;
}