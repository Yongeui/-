package User;

public class User {
	private String 	username;
	private String 	email;
	private String 	password;
	private String 	address;
	private String 	phonenumber;

	// 이름
	public String getusername() {
		return username;
	}
	public void setusername(String username) {
		this.username = username;
	}
	// 끝
	
	// 이메일
	public String getemail() {
		return email;
	}
	public void setemail(String email) {
		this.email = email;
	}
	//이메일 끝
	
	//비번
	public String getpassword() {
		return password;
	}
	public void setpassword(String password) {
		this.password = password;
	}
	//비번 끝
	
	// 주소
	public String getaddress() {
		return address;
	}
	public void setaddress(String address) {
		this.address = address;
	}
	// 주소  끝
	
	//전화번호
	public String getphonenumber() {
		return phonenumber;
	}
	public void setphonenumber(String phonenumber) {
		this.phonenumber = phonenumber;
	}
	// 전화번호 끝
}