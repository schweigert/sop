enderecos = [3000,6000,9000]
pag = 2*2**10

tab = [
	[ 3,	false], 	#0
	[ 2,	true], 	#1
	[ 7,	false], 	#2
	[11,	false], 	#3
	[ 5,	true], 	#4
	[ 8,	true], 	#5
	[ 9,	false], 	#6
	[10,	true]  	#7
]

puts "Pagina: #{pag}"

for i in tab
 puts "#{i[0]}\t#{i[1]}"
end


for i in enderecos

	puts "\n\tCaso: #{i}"
	p = i/pag
	d = i%pag
	
	f = tab[p][0]
	existe = tab[p][1]

	puts "EF = (#{f}*#{pag}) + #{d}"
	puts "EF = #{(f*pag) + d}"
	
	if not existe
		puts "Pagina nao existente"
	end
	

end	
