#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <htslib/sam.h>

int main(int argc, char *argv[]){
  if (argc < 2) {
    printf("Should run with an input bam file\n");
    exit(-1);
  }
	
  samFile *fp_in = hts_open(argv[1],"r"); //open bam file
  bam_hdr_t *bamHdr = sam_hdr_read(fp_in); //read header
  bam1_t *aln = bam_init1(); //initialize an alignment
  
  // header parse
  // uint32_t *tar = bamHdr->text ;
  // uint32_t *tarlen = bamHdr->target_len ;

  // printf("%d\n",tar);
  
  while(sam_read1(fp_in,bamHdr,aln) > 0){
          
    int32_t pos = aln->core.pos +1; //left most position of alignment in zero based coordinate (+1)
    char *chr = bamHdr->target_name[aln->core.tid] ; //contig name (chromosome)
    uint32_t len = aln->core.l_qseq; //length of the read.
    
    uint8_t *q = bam_get_seq(aln); //quality string
    uint32_t q2 = aln->core.qual ; //mapping quality
		
		
    char *qseq = (char *)malloc(len);
    
    for(int i=0; i< len ; i++){
      qseq[i] = seq_nt16_str[bam_seqi(q,i)]; //gets nucleotide id and converts them into IUPAC id.
    }
    
    //printf("chr=%s\tpos=%d\tlen=%d\tqseq=%s\tq=%s\tq2=%d\n",chr,pos,len,qseq,q,q2);
    printf("chr=%s\tpos=%d\tlen=%d\tqseq=%s\tq2=%d\n",chr,pos,len,qseq,q2);

  }
  
  bam_destroy1(aln);
  sam_close(fp_in);
  
  return 0;
}
