<?

function accountcreate($username, $password, $connection, $bandwidth, $disabledate, $disabletime)
{
	$adminpassword='admin';
	$adminport=88;
	$proxyaddress='mail.ccproxy.com';

	$fp = fsockopen($proxyaddress, $adminport, &$errno, &$errstr, 1000);
	if(!$fp) 
	{
        	echo "$errstr ($errno)<br>\n";
	} 
	else 
	{
		$url_ = "/account";
		$url = "add=1"."&";
		$url = $url."autodisable=1"."&";
		$url = $url."enable=1"."&";
		$url = $url."usepassword=1"."&";
		$url = $url."enablesocks=1"."&";
		$url = $url."enablewww=0"."&";
		$url = $url."enabletelnet=0"."&";
		$url = $url."enabledial=0"."&";
		$url = $url."enableftp=0"."&";
		$url = $url."enableothers=0"."&";
		$url = $url."enablemail=0"."&";
		$url = $url."username=".$username."&";
		$url = $url."password=".$password."&";
		$url = $url."connection=".$connection."&";
		$url = $url."bandwidth=".$bandwidth."&";
		$url = $url."disabledate=".$disabledate."&";
		$url = $url."disabletime=".$disabletime."&";
		$url = $url."userid=-1";
		$len = "Content-Length: ".strlen($url);
		$auth = "Authorization: Basic ".base64_encode("admin:".$adminpassword);
		$msg = "POST ".$url_." HTTP/1.0\r\nHost: ".$proxyaddress."\r\n".$auth."\r\n".$len."\r\n"."\r\n".$url;
        	fputs($fp,$msg);
		//echo $msg;
		while(!feof($fp)) 
		{
			$s = fgets($fp,4096);
			//echo $s;
		}
		fclose($fp);
	}

}

accountcreate("test", "111", "1", "20", "2005-05-30", "20:20:20");
?>