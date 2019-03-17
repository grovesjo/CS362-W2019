import static org.junit.Assert.*;

import org.junit.Test;

public class UrlValidatorTest {

	/////////////////////////////////////////////////////////////////////////////
	// Begin Scheme testing
	/////////////////////////////////////////////////////////////////////////////	
	
	@Test
	public void schemeTest_Null() {
		UrlValidator urlTest = new UrlValidator();	
		String testStr = "www.oregonstate.edu";
		assertFalse(urlTest.isValid(testStr));		
	}

	@Test
	public void schemeTest_http() {
		UrlValidator urlTest = new UrlValidator();	
		String testStr = "http://www.oregonstate.edu";
		assertTrue(urlTest.isValid(testStr));		
	}	 

	@Test
	public void schemeTest_HTTPS() {
		UrlValidator urlTest = new UrlValidator();	
		String testStr = "HTTPS://www.oregonstate.edu";
		assertTrue(urlTest.isValid(testStr));		
	}
	
	@Test
	public void schemeTest_fTp() {
		UrlValidator urlTest = new UrlValidator();	
		String testStr = "fTp://www.oregonstate.edu";
		assertTrue(urlTest.isValid(testStr));	
	}	
	

	@Test
	public void schemeTest_0123() {
		UrlValidator urlTest = new UrlValidator();	
		String testStr = "0123://www.oregonstate.edu";
		assertFalse(urlTest.isValid(testStr));		
	}
	
	@Test
	public void schemeTest_abc() {
		UrlValidator urlTest = new UrlValidator();	
		String testStr = "abc://www.oregonstate.edu";
		assertFalse(urlTest.isValid(testStr));		
	}
	
	@Test
	public void schemeTest_ABC() {
		UrlValidator urlTest = new UrlValidator();	
		String testStr = "ABC://www.oregonstate.edu";
		assertFalse(urlTest.isValid(testStr));		
	}
	
	@Test
	public void schemeTest_0123_schemes() {
		String[] schemes = {"0123"};
		UrlValidator urlTest = new UrlValidator(schemes);	
		String testStr = "0123://www.oregonstate.edu";
		assertFalse(urlTest.isValid(testStr));		
	}	
	
	@Test
	public void schemeTest_abc_schemes() {
		String[] schemes = {"abc"};
		UrlValidator urlTest = new UrlValidator(schemes);
		String testStr = "abc://www.oregonstate.edu";
		assertTrue(urlTest.isValid(testStr));		
	}
	
	@Test
	public void schemeTest_ABC_schemes() {
		String[] schemes = {"ABC"};
		UrlValidator urlTest = new UrlValidator(schemes);	
		String testStr = "ABC://www.oregonstate.edu";
 		assertTrue(urlTest.isValid(testStr));		
	}
	
	
	@Test
	public void schemeTest_ABC_allowallschemes() {
		UrlValidator urlTest = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	
		String testStr = "ABC://www.oregonstate.edu";
		assertTrue(urlTest.isValid(testStr));		
	}	
	
	@Test
	public void schemeTest_http_allowallschemes() {
		UrlValidator urlTest = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	
		String testStr = "http://www.oregonstate.edu";
		assertTrue(urlTest.isValid(testStr));		
	}	
	
	@Test
	public void schemeTest_https_allowallschemes() {
		UrlValidator urlTest = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	
		String testStr = "https://www.oregonstate.edu";
		assertTrue(urlTest.isValid(testStr));		
	}		
	
	/////////////////////////////////////////////////////////////////////////////
	// Begin Authority testing
	// Testing domain, IPv4, IPv6, ports
	/////////////////////////////////////////////////////////////////////////////	

	@Test
	public void authTest_http_valid_domain_allowallschemes() {
		UrlValidator urlTest = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	
		String testStr = "http://www.google.com";
		assertTrue(urlTest.isValid(testStr));		
	}	

	@Test
	public void authTest_http_invalid_nulldomain_allowallschemes() {
		UrlValidator urlTest = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	
		String testStr = "http://";
		assertFalse(urlTest.isValid(testStr));		
	}	

	@Test
	public void authTest_http_invalid_nullTLD_allowallschemes() {
		UrlValidator urlTest = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	
		String testStr = "http://google";
		assertFalse(urlTest.isValid(testStr));		
	}	
	
	@Test
	public void authTest_http_invalid_TLD_allowallschemes() {
		UrlValidator urlTest = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	
		String testStr = "http://www.google.darpa";
		assertFalse(urlTest.isValid(testStr));		
	}	
	
	@Test
	public void authTest_http_valid_ipv4_allowallschemes() {
		UrlValidator urlTest = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	
		String testStr = "http://192.168.1.1";
		assertTrue(urlTest.isValid(testStr));		
	}	

	@Test
	public void authTest_http_invalid_ipv4_allowallschemes() {
		UrlValidator urlTest = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	
		String testStr = "http://192.256.1.1";
		assertFalse(urlTest.isValid(testStr));		
	}		

	@Test
	public void authTest_http_valid_ipv6_allowallschemes() {
		UrlValidator urlTest = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	
		String testStr = "http://2600:2700:1d40:d360:804a:a732:e5b4:7b18";
		assertTrue(urlTest.isValid(testStr));		
	}	

	@Test
	public void authTest_http_valid_ipv6_brackets_allowallschemes() {
		UrlValidator urlTest = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	
		String testStr = "http://[2600:2700:1d40:d360:804a:a732:e5b4:7b18]";
		assertTrue(urlTest.isValid(testStr));		
	}
	
	@Test
	public void authTest_http_invalid_ipv6_allowallschemes() {
		UrlValidator urlTest = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	
		String testStr = "http://2600:2700:1d40:g360:804a:a732:e5b4:7b18";
		assertFalse(urlTest.isValid(testStr));		
	}	
	
	
	@Test
	public void authTest_http_validport_allowallschemes() {
		UrlValidator urlTest = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	
		String testStr = "http://www.oregonstate.edu:80";
		assertTrue(urlTest.isValid(testStr));		
	}		
	
	@Test
	public void authTest_http_invalidport_mix_allowallschemes() {
		UrlValidator urlTest = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	
		String testStr = "http://www.oregonstate.edu:65a";
		assertFalse(urlTest.isValid(testStr));		
	}	
	
	@Test
	public void authTest_http_invalidport_99999_allowallschemes() {
		UrlValidator urlTest = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	
		String testStr = "http://www.oregonstate.edu:99999";
		assertFalse(urlTest.isValid(testStr));		
	}
	
	@Test
	public void authTest_http_invalidport_Neg1_allowallschemes() {
		UrlValidator urlTest = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	
		String testStr = "http://www.oregonstate.edu:-1";
		assertFalse(urlTest.isValid(testStr));		
	}	

	@Test
	public void authTest_http_invalidport_zzz_allowallschemes() {
		UrlValidator urlTest = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	
		String testStr = "http://www.oregonstate.edu:zzz";
		assertFalse(urlTest.isValid(testStr));		
	}	
	
	@Test
	public void authTest_http_valid_ipv4_port_allowallschemes() {
		UrlValidator urlTest = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	
		String testStr = "http://192.168.1.1:80";
		assertTrue(urlTest.isValid(testStr));		
	}
	
	@Test
	public void authTest_http_valid_ipv6_port_allowallschemes() {
		UrlValidator urlTest = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	
		String testStr = "http://2600:2700:1d40:d360:804a:a732:e5b4:7b18:25";
		assertTrue(urlTest.isValid(testStr));		
	}	
	

	/////////////////////////////////////////////////////////////////////////////
	// Begin Path testing
	/////////////////////////////////////////////////////////////////////////////	
	
	@Test
	public void pathTest_http_valid_emptyPath_allowallschemes() {
		UrlValidator urlTest = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	
		String testStr = "http://www.google.com";
		assertTrue(urlTest.isValid(testStr));		
	}

	@Test
	public void pathTest_http_valid_allowallschemes() {
		UrlValidator urlTest = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	
		String testStr = "http://www.google.com/gmail";
		assertTrue(urlTest.isValid(testStr));		
	}

	@Test
	public void pathTest_http_valid_multipledir_allowallschemes() {
		UrlValidator urlTest = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	
		String testStr = "http://www.google.com/more/more/more/more/more/more/more/more/gmail";
		assertTrue(urlTest.isValid(testStr));		
	}
	
	@Test
	public void pathTest_http_valid_fileName_allowallschemes() {
		UrlValidator urlTest = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	
		String testStr = "http://www.google.com/gmail.html";
		assertTrue(urlTest.isValid(testStr));		
	}

	@Test
	public void pathTest_http_invalid_doubleSlash_allowallschemes() {
		UrlValidator urlTest = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	
		String testStr = "http://www.google.com//";
		assertFalse(urlTest.isValid(testStr));		
	}

	@Test
	public void pathTest_http_invalid_doublePeriod_allowallschemes() {
		UrlValidator urlTest = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	
		String testStr = "http://www.google.com/../";
		assertFalse(urlTest.isValid(testStr));		
	}	
	/////////////////////////////////////////////////////////////////////////////
	// Begin Query testing
	/////////////////////////////////////////////////////////////////////////////
	
	@Test
	public void queryTest_http_valid_allowallschemes() {
		UrlValidator urlTest = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	
		String testStr = "http://www.google.com/home.html?username=admin";
		assertTrue(urlTest.isValid(testStr));		
	}

	@Test
	public void queryTest_http_invalid_allowallschemes() {
		UrlValidator urlTest = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	
		String testStr = "http://www.google.com/home.html?password=pass word";
		assertFalse(urlTest.isValid(testStr));
	}	
		
	
}	
