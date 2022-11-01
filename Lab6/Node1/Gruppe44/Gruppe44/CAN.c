#include "CAN.h"


uint8_t CAN_init ()
{
	uint8_t value ;
	SPI_init () ; // Initialize SPI
	CAN_reset () ; // Send reset - command
	// Self - test
	value = CAN_read ( MCP_CANSTAT);
	if (( value & MODE_MASK ) != MODE_CONFIG ) {
		printf (" MCP2515 is NOT in configuration mode after reset !\n");
		return 1;
	}
	// More initialization
	
	// Config - page 44 in MCP datasheet
	CAN_bit_modify(MCP_CNF1, 0xFF, 0b10000010); 
	CAN_bit_modify(MCP_CNF2, 0xFF, 0b11111001);
	CAN_bit_modify(MCP_CNF3, 0xC7, 0b00000111);
	
	
	
	//CAN_bit_modify(MCP_RXM0SIDH, 0xF0, 0xF0);
	//CAN_bit_modify(MCP_RXM0SIDL, )
	
	//CAN_bit_modify(MCP_RXF0SIDH, 0xF0, 0x00);
	//CAN_bit_modify(MCP_RXF0SIDL, )
	
	CAN_bit_modify(MCP_RXB0CTRL, 0x60, 0b00100000);
	CAN_bit_modify(MCP_CANINTE, 0x01, 0x01);
	
	
	CAN_bit_modify(MCP_CANCTRL, 0xE0, MODE_LOOPBACK);
	return 0;
}

uint8_t CAN_read ( uint8_t address )
{
	uint8_t result ;
	PORTB &= ~(1 << CAN_CS ); // Select CAN - controller
	SPI_write ( MCP_READ ); // Send read instruction
	SPI_write ( address );
	result = SPI_read () ; // Read result
	PORTB |= (1 << CAN_CS ); // Deselect CAN - controller
	return result ;
}

CAN_write( uint8_t address, uint8_t data ){
	PORTB &= ~(1 << CAN_CS ); // Select CAN - controller
	SPI_write ( MCP_WRITE );
	SPI_write (address);
	SPI_write (data);
	PORTB |= (1 << CAN_CS ); // Deselect CAN - controller
}

CAN_request_to_send( uint8_t PortNumber ){
	PortNumber |= 0x07;
	PORTB &= ~(1 << CAN_CS ); // Select CAN - controller
	SPI_write ( (PortNumber)|(0x80) ); // Check which of the TX0, TX1 or TX2 ports we use MCP_RST_PortNumber
	PORTB |= (1 << CAN_CS ); // Deselect CAN - controller
}

CAN_bit_modify( uint8_t bit_address , uint8_t mask_byte, uint8_t data_byte){
	PORTB &= ~(1 << CAN_CS ); // Select CAN - controller
	SPI_write ( MCP_BITMOD ); // Bit modification command
	SPI_write ( bit_address ); // address
	SPI_write ( mask_byte ); // mask byte
	SPI_write ( data_byte ); // data byte
	PORTB |= (1 << CAN_CS ); // Deselect CAN - controller
}

CAN_reset(){
	PORTB &= ~(1 << CAN_CS ); // Select CAN - controller
	SPI_write ( MCP_RESET ); // Reset command
	PORTB |= (1 << CAN_CS ); // Deselect CAN - controller
}

CAN_read_status(){
	uint8_t received;
	PORTB &= ~(1 << CAN_CS ); // Select CAN - controller
	SPI_transmit( MCP_CANSTAT ); // Read status
	received = SPI_transmit(0xff);
	PORTB |= (1 << CAN_CS ); // Deselect CAN - controller
	return received;
}

CAN_write_message(struct Can_Message message){
	
	while ((CAN_read(MCP_TXB0CTRL) & (1<<3))){}
	//TODO: Send id to two register, len to one, then data, then request to send.
	CAN_write(MCP_TXB0_ID_LOW, (message.id & 0x07) << 5);
	
	CAN_write(MCP_TXB0_ID_HIGH, (message.id >> 3) & 0xFF );
	
	
	
	//printf("%hd \r \n", (message.id << 5) & 0xFF);
	//printf("%hd \r \n", message.id >> 3);
	//printf("message length: %i \r \n", message.length);
	CAN_write(MCP_TXB0_LEN, message.length);
	
	for (int i = 0; i<message.length; i++){
		CAN_write(MCP_TXB0_DATA + i, message.data[i]);
		_delay_ms(10);
	}
	
}

struct Can_Message CAN_read_message(){
	
	
	struct Can_Message recieved_message;
	
	_delay_ms(10);
	recieved_message.length = CAN_read(MCP_RXB0_LEN) & 0x0F ;
	//recieved_message.length = CAN_read(MCP_RXB0_LEN) & 0x0F;
	
	_delay_ms(10);
	recieved_message.id = ((CAN_read(MCP_RXB0_ID_HIGH) << 3) | (CAN_read(MCP_RXB0_ID_LOW) >> 5)) & 0xFF;
	//printf("received length: %x \n", recieved_message.length);
	
	for (int i = 0; i<recieved_message.length; i++){
		recieved_message.data[i] = CAN_read(MCP_RXB0_DATA + i);
		_delay_ms(10);
	}
	
	CAN_bit_modify(MCP_CANINTF, 0x01, 0x00);

	
	return recieved_message;
}